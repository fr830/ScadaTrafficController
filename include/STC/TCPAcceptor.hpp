#ifndef INCLUDE_STC_TCPACCEPTOR_HPP
#define INCLUDE_STC_TCPACCEPTOR_HPP
#include <STC/Acceptor.hpp>
#include <STC/TCPHeader.hpp>
#include <vector>
#include <cstdint>
#include <cstddef>
#include <memory>
#include <optional>

namespace stc
{

namespace network
{


class TCPAcceptor:
        public Acceptor
{
public:
    TCPAcceptor(std::shared_ptr<Acceptor> acceptor);
    void accept(std::byte const * ptr, uint32_t size) noexcept override;
    void timeout() noexcept override;
private:
    void resetPacketData() noexcept;
    std::vector<std::byte> mData;
    std::shared_ptr<Acceptor> mAcceptor;
    std::optional<TCPHeader> mHeader;
};


}//namespace network
}//namespace stc


#endif //INCLUDE_STC_TCPACCEPTOR_HPP
