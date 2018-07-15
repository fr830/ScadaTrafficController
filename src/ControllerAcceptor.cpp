#include <STC/ControllerAcceptor.hpp>
#include <STC/Controller.hpp>
#include <algorithm>

namespace stc
{

ControllerAcceptor::ControllerAcceptor(std::shared_ptr<Controller> controller):
    mController(std::move(controller))
{
}

void ControllerAcceptor::accept(std::byte const * ptr, uint32_t size) noexcept
{
    char const * data_begin = reinterpret_cast<char const *>(ptr);
    char const * data_end = reinterpret_cast<char const *>(ptr) + size;
    auto is_null = [](char b) { return !b; };
    data_begin = std::find_if_not(data_begin, data_end, is_null);
    data_end = std::find_if(data_begin, data_end, is_null);
    if (data_begin != data_end) {
        if (*data_begin == '<' && *(data_end - 1) == '>') {
            mActualData.assign(data_begin + 1, data_end - 1);
            if (!mActualData.empty()) {
                Event event;
                event.mType = EventType::Update;
                event.mData.emplace<Event::ETUpdate>(
                    std::make_pair(mController, mActualData)
                    );
                mController->getEventsPool()->pushEvent(std::move(event));
            }
        }
    }
}

}//namespace stc
