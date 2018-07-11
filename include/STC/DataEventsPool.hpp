#ifndef INCLUDE_STC_DATAEVENTSPOOL_HPP
#define INCLUDE_STC_DATAEVENTSPOOL_HPP
#include <STC/MultithreadQueue.hpp>
#include <variant>
#include <functional>
#include <condition_variable>

namespace stc
{


enum class EventType
{
    Update,
    UpdateTimeout
};


struct Event
{
    using Data = std::vector<std::vector<std::string>>;
    EventType mType;
    std::variant<Data, std::string> mData;
};


class DataEventsPool
{
public:
    void pushEvent(Event & event);
    void pushEvent(Event && event);
    bool popEvent(Event & event);
    bool popEventIf(Event & event, std::function<bool(Event const &)> func);

    void waitEvent(Event & event);
private:
    core::MultithreadQueue<Event> mEventsPool;
    std::condition_variable mCv;
    std::mutex mCvMutex;
};


}//namespace stc



#endif //INCLUDE_STC_DATAEVENTSPOOL_HPP
