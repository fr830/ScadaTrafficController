#include "STC/SafeAPI.hpp"
#include "STC/MemoryTools.hpp"
#include <iphlpapi.h>

namespace stc
{


std::unique_ptr<IP_ADAPTER_INFO, ::stc::BufferDeletor> SafeGetAdaptersInfo()
{
    std::unique_ptr<IP_ADAPTER_INFO, ::stc::BufferDeletor> result;
    ULONG bufferSize = sizeof(IP_ADAPTER_INFO);
    result.reset(reinterpret_cast<PIP_ADAPTER_INFO>(alloc_buffer(bufferSize)));

    DWORD getinfo_result = NO_ERROR;
    while ((getinfo_result = GetAdaptersInfo(result.get(), &bufferSize)) == ERROR_BUFFER_OVERFLOW) {
        result.reset(reinterpret_cast<PIP_ADAPTER_INFO>(alloc_buffer(bufferSize)));
    }

    if (getinfo_result != NO_ERROR) {
        throw AdaptersInfoFailure(
            L"GetAdaptersInfo failure with error code " + std::to_wstring(getinfo_result)
        );
    }
    return result;
}

std::pair<DWORD, std::wstring> SafeGetLastError(bool generate_text)
{
    LPWSTR errText = nullptr;
    auto errCode = GetLastError();
    if (generate_text)
    {
        DWORD fmres = FormatMessageW(
           FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER ,
           nullptr,
           errCode,
           MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US),
           reinterpret_cast<LPWSTR>(&errText),
           0,
           nullptr);

        if (errText == nullptr)
        {
           throw ::stc::FormatMessageFailure{
                L"FormatMessage failure with error code " + std::to_wstring(fmres)
           };
        }
    }

    try {
        std::pair<DWORD, std::wstring> result = {errCode, (generate_text? errText: L"")};
        LocalFree(errText);
        return result;
    } catch (...) {
        LocalFree(errText);
        throw;
    }
}


}//namespace stc
