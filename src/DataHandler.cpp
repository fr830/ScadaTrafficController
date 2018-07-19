#include <STC/DataHandler.hpp>
#include <STC/DataPacket.hpp>

namespace stc
{

void data_event_handler(std::shared_ptr<DataEventsPool> events_pool)
{
    stc::Event event;
    stc::DataPacket packet;
    events_pool->waitEvent(event);
    while (event.mType != stc::EventType::Close) {
        bool has_event = true;
        while(has_event && event.mType != stc::EventType::Close) {
            switch (event.mType) {
            case stc::EventType::Update:
                {
                    auto & [controller, data_string] = std::get<
                            static_cast<size_t>(stc::EventType::Update)
                            >(event.mData);

                    packet.parseFromString(data_string);
                    controller->setActualPacket(packet);
                    controller->setSignalState(true);
                    break;
                }
            case stc::EventType::UpdateTimeout:
                {
                    auto controller = std::get<
                            static_cast<size_t>(stc::EventType::UpdateTimeout)
                            >(event.mData);
                    controller->setSignalState(false);
                    break;
                }
            default:
                break;
            }
            has_event = events_pool->popEvent(event);
        }
        events_pool->waitEvent(event);
    }
}

}//namespace stc
