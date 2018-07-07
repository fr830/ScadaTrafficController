#ifndef INCLUDE_STC_FILTEREDIPV4TCPACCEPTOR_HPP
#define INCLUDE_STC_FILTEREDIPV4TCPACCEPTOR_HPP


#include <STC/Acceptor.hpp>
#include <STC/IPv4Converter.hpp>
#include <STC/IPv4Header.hpp>
#include <vector>
#include <memory>
#include <cstdint>

namespace stc
{
namespace network
{


class FilterIPv4Options
{
public:
    enum class Protocol: uint8_t
    {
        TCP = 0x06
    };
    FilterIPv4Options(std::shared_ptr<Acceptor> acceptor,
                      IPv4Converter ip, Protocol protocol
                      );
    FilterIPv4Options(FilterIPv4Options const &) = default;
    FilterIPv4Options(FilterIPv4Options &&) noexcept = default;
    FilterIPv4Options & operator=(FilterIPv4Options const &) = default;
    FilterIPv4Options & operator=(FilterIPv4Options &&) noexcept = default;
    std::shared_ptr<Acceptor> const & acceptor() const noexcept;
    uint32_t ip() const noexcept;
    Protocol protocol() const noexcept;
private:
    std::shared_ptr<Acceptor> mAcceptor;
    uint32_t mIP;
    Protocol mProtocol;
};


inline bool operator==(FilterIPv4Options::Protocol f, int s) noexcept
{
    return static_cast<uint8_t>(f) == s;
}

inline bool operator==(int f, FilterIPv4Options::Protocol s) noexcept
{
    return s == f;
}

inline bool operator!=(FilterIPv4Options::Protocol f, int s) noexcept
{
    return !(f == s);
}

inline bool operator!=(int f, FilterIPv4Options::Protocol s) noexcept
{
    return !(s == f);
}




class FilteredIPv4Acceptor:
        public ::stc::network::Acceptor
{
public:
    FilteredIPv4Acceptor(std::vector<FilterIPv4Options> options);
    void accept(std::byte const * ptr, uint32_t size) noexcept override;
private:
    std::vector<FilterIPv4Options> mOptions;
};


}//namespace network
}//namespace stc



#endif //INCLUDE_STC_FILTEREDIPV4TCPACCEPTOR_HPP
