#include <STC/DataHandler.hpp>


namespace stc
{

void data_event_handler(std::shared_ptr<DataEventsPool> events_pool)
{
    stc::Event event;
    events_pool->waitEvent(event);
    while (event.mType != stc::EventType::Close) {
        bool has_event = true;
        while(has_event && event.mType != stc::EventType::Close) {
            has_event = events_pool->popEvent(event);

            switch (event.mType) {
            case stc::EventType::Update:
                std::get<(int)stc::EventType::Update>(event.mData);
                break;
            default:
                break;
            }
        }
        events_pool->waitEvent(event);
    }
}

}//namespace stc
