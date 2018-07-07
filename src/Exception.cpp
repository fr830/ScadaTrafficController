#include "STC/Exception.hpp"

namespace stc
{

Exception::Exception(std::wstring str):
    mMessage(std::move(str))
{
}

Exception::~Exception()
{
}

wchar_t const * Exception::message() const noexcept
{
    return mMessage.c_str();
}



}//namespace stc



