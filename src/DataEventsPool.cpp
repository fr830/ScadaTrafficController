#include <STC/DataEventsPool.hpp>


namespace stc
{

void DataEventsPool::pushEvent(Event & event)
{
    mEventsPool.emplace(event);
}

void DataEventsPool::pushEvent(Event && event)
{
    mEventsPool.emplace(std::move(event));
}

bool DataEventsPool::popEvent(Event & event)
{
    return mEventsPool.pop(event);
}

bool DataEventsPool::popEventIf(Event & event, std::function<bool(Event const &)> func)
{
    return mEventsPool.popIf(event, func);
}



}//namespace stc


