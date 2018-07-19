#ifndef INCLUDE_STC_CONTROLLERACCEPTOR_HPP
#define INCLUDE_STC_CONTROLLERACCEPTOR_HPP
#include <STC/Acceptor.hpp>
#include <STC/DataEventsPool.hpp>
#include <memory>
#include <cstddef>
#include <cstdint>

namespace stc
{


class Controller;
class ControllerAcceptor:
        public ::stc::network::Acceptor
{
public:

    ControllerAcceptor(std::shared_ptr<Controller> controller,
                       std::shared_ptr<stc::DataEventsPool> events_pool
                       );
    void accept(std::byte const * ptr, uint32_t size) noexcept override;
    void timeout() noexcept override;
private:
    std::shared_ptr<stc::DataEventsPool> mEventsPool;
    std::shared_ptr<Controller> mController;
    std::string mActualData;
};



}//namespace stc


#endif //INCLUDE_STC_CONTROLLERACCEPTOR_HPP
