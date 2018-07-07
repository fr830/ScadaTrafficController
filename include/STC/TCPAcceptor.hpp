#ifndef INCLUDE_STC_TCPACCEPTOR_HPP
#define INCLUDE_STC_TCPACCEPTOR_HPP
#include <STC/Acceptor.hpp>
#include <STC/TCPHeader.hpp>
#include <vector>
#include <cstdint>
#include <cstddef>

namespace stc
{

namespace network
{


class TCPAcceptor:
        public Acceptor
{
public:
    void accept(std::byte const * ptr, uint32_t size) noexcept override;
private:
    TCPHeader mHeader;
    std::vector<std::byte> mData;
};


}//namespace network
}//namespace stc


#endif //INCLUDE_STC_TCPACCEPTOR_HPP
