#ifndef INCLUDE_STC_MULTITHREADQUEUE_HPP
#define INCLUDE_STC_MULTITHREADQUEUE_HPP

#include <queue>
#include <mutex>



namespace stc
{


namespace core
{


template<typename T>
class MultithreadQueue
{
public:
    bool isEmpty() noexcept
    {
        auto locker = getLock();
        return usIsEmpty();
    }

    template<typename ... Args>
    void emplace(Args && ... args)
    {
        auto locker = getLock();
        usEmplace(std::forward<Args>(args)...);
    }

    bool pop(T & old)
    {
        auto locker = getLock();
        return usPop(old);
    }

    bool pop()
    {
        auto locker = getLock();
        return usPop();
    }

    template<typename Function>
    bool popIf(T & old, Function func)
    {
        auto locker = getLock();
        return usPopIf(old, func);
    }

    template<typename Function>
    bool popIf(Function func)
    {
        auto locker = getLock();
        return usPopIf(func);
    }

private:
    bool usIsEmpty() noexcept
    {
        return mQueue.empty();
    }


    std::lock_guard<std::mutex> getLock()
    {
        return std::lock_guard<std::mutex>{mMutex};
    }

    template<typename ... Args>
    void usEmplace(Args && ... args)
    {
        mQueue.emplace(std::forward<Args>(args)...);
    }

    bool usPop(T & old)
    {
        if (!usIsEmpty()) {
            old = std::move(mQueue.front());
            mQueue.pop();
            return true;
        }
        return false;
    }

    bool usPop()
    {
        if (!usIsEmpty()) {
            mQueue.pop();
            return true;
        }
        return false;
    }

    template<typename Function>
    bool usPopIf(T & old, Function func)
    {
        if (!usIsEmpty()) {
            if (func(mQueue.front())) {
                old = std::move(mQueue.front());
                mQueue.pop();
                return true;
            }
        }
        return false;
    }

    template<typename Function>
    bool usPopIf(Function func)
    {
        if (func(mQueue.front())) {
            usPop();
            return true;
        }
        return false;
    }

    std::queue<T> mQueue;
    std::mutex mMutex;
};



}//namespace core
}//namespace stc

#endif //INCLUDE_STC_MULTITHREADQUEUE_HPP
