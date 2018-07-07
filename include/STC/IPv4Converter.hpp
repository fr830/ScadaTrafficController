#ifndef INCLUDE_STC_IPV4CONVERTER_HPP
#define INCLUDE_STC_IPV4CONVERTER_HPP

#include <cstdint>

namespace stc
{
namespace network
{

class IPv4Converter
{
public:
    IPv4Converter(char const * ip_str) noexcept;
    IPv4Converter(uint32_t ip_be) noexcept;
    uint32_t getIpBE() const noexcept;
    operator uint32_t() const noexcept;
private:
    uint32_t mIP;
};

}//namespace network
}//namespace stc



#endif //INCLUDE_STC_IPCONVERTER_HPP
