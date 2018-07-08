#ifndef INCLUDE_STC_CONTROLLERACCEPTOR_HPP
#define INCLUDE_STC_CONTROLLERACCEPTOR_HPP
#include <STC/Acceptor.hpp>
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
    ControllerAcceptor(std::shared_ptr<Controller> controller);
    void accept(std::byte const * ptr, uint32_t size) noexcept override;
private:
    std::shared_ptr<Controller> mController;
    std::string mActualData;
};



}//namespace stc


#endif //INCLUDE_STC_CONTROLLERACCEPTOR_HPP
