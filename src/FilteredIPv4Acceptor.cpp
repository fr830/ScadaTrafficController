#include <STC/FilteredIPv4Acceptor.hpp>
#include <STC/IPv4Header.hpp>
#include <algorithm>

namespace stc
{
namespace network
{


FilteredIPv4Acceptor::FilteredIPv4Acceptor(
        std::vector<FilterIPv4Options> options
        )
    : mOptions(std::move(options))
{
}

void FilteredIPv4Acceptor::accept(std::byte const * ptr, uint32_t size) noexcept
{
    IPv4Header const * ip_header = reinterpret_cast<IPv4Header const *>(ptr);
    if (
        size < sizeof(IPv4Header) ||
        ip_header->mIpVersion != 4
        ) {
        return;
    }
    for (auto option: mOptions) {
        if (option.ip() == ip_header->mSourceIP &&
            option.protocol() == ip_header->mProtocol
        ) {
            uint32_t size_ip_headers = ip_header->mHeaderSize * 4;
            option.acceptor()->accept(
                        ptr + size_ip_headers,
                        size - size_ip_headers
                        );
        }
    }
}



FilterIPv4Options::FilterIPv4Options(
        std::shared_ptr<Acceptor> acceptor,
        IPv4Converter ip, Protocol protocol
        ):
    mAcceptor(std::move(acceptor)),
    mIP(ip),
    mProtocol(protocol)
{
}


std::shared_ptr<Acceptor> const & FilterIPv4Options::acceptor() const noexcept
{
    return mAcceptor;
}

uint32_t FilterIPv4Options::ip() const noexcept
{
    return mIP;
}

FilterIPv4Options::Protocol FilterIPv4Options::protocol() const noexcept
{
    return mProtocol;
}





}//namespace network
}//namespace stc
