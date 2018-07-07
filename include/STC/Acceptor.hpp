#ifndef INCLUDE_STC_ACCEPTOR_HPP
#define INCLUDE_STC_ACCEPTOR_HPP
#include <cstddef>
#include <cstdint>

namespace stc
{
namespace network
{


class Acceptor
{
public:
    virtual void accept(std::byte const * ptr, uint32_t size) noexcept = 0;
    virtual ~Acceptor() = default;
};


}//namespace network
}//namespace stc


#endif //INCLUDE_STC_ACCEPTOR_HPP
