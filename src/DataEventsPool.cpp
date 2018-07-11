#include <STC/DataEventsPool.hpp>


namespace stc
{

void DataEventsPool::pushEvent(Event & event)
{
    mEventsPool.emplace(event);
    mCv.notify_one();
}

void DataEventsPool::pushEvent(Event && event)
{
    mEventsPool.emplace(std::move(event));
    mCv.notify_one();
}

bool DataEventsPool::popEvent(Event & event)
{
    return mEventsPool.pop(event);
}

bool DataEventsPool::popEventIf(Event & event, std::function<bool(Event const &)> func)
{
    return mEventsPool.popIf(event, func);
}

void DataEventsPool::waitEvent(Event & event)
{
    std::unique_lock<std::mutex> locker(mCvMutex);
    mCv.wait(locker, [&event, this]{return this->popEvent(event);});
    mCvMutex.unlock();
}



}//namespace stc


