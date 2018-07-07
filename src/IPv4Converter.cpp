#include <STC/IPv4Converter.hpp>
#include <winsock2.h>
namespace stc
{
namespace network
{

IPv4Converter::IPv4Converter(char const * ip_str) noexcept:
    mIP(inet_addr(ip_str))
{
}

IPv4Converter::IPv4Converter(uint32_t ip_be) noexcept:
    mIP(ip_be)
{
}


uint32_t IPv4Converter::getIpBE() const noexcept
{
    return mIP;
}

stc::network::IPv4Converter::operator uint32_t() const noexcept
{
    return mIP;
}





}//namespace network
}//namespace stc
