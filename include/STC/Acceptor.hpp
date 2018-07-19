#ifndef INCLUDE_STC_ACCEPTOR_HPP
#define INCLUDE_STC_ACCEPTOR_HPP
#include <cstddef>
#include <cstdint>
#include <chrono>

namespace stc
{
namespace network
{


class Acceptor
{
public:
    using TimeClock = std::chrono::steady_clock;
    using TimePoint = TimeClock::time_point;
    using Duration = TimeClock::duration;
    virtual void accept(std::byte const * ptr, uint32_t size) noexcept = 0;
    virtual void timeout() noexcept = 0;
    virtual ~Acceptor() = default;
};


}//namespace network
}//namespace stc


#endif //INCLUDE_STC_ACCEPTOR_HPP
