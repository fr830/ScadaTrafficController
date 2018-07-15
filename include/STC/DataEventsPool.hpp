#ifndef INCLUDE_STC_DATAEVENTSPOOL_HPP
#define INCLUDE_STC_DATAEVENTSPOOL_HPP
#include <STC/MultithreadQueue.hpp>
#include <variant>
#include <functional>
#include <condition_variable>
#include <memory>

namespace stc
{

class Controller;


enum class EventType
{
    Update,
    UpdateTimeout,
    Close
};


struct Event
{
    using Data = std::vector<std::vector<std::string>>;
    using ETUpdate = std::pair<std::shared_ptr<Controller>, std::string>;
    using ETUpdateTimeout = std::shared_ptr<Controller>;
    EventType mType;
    std::variant<Data, ETUpdate, ETUpdateTimeout> mData;
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
