#ifndef INCLUDE_STC_CONTROLLER_HPP
#define INCLUDE_STC_CONTROLLER_HPP
#include <string>
#include <vector>
#include <mutex>
#include <chrono>
#include <atomic>
#include <future>

namespace stc
{


class Controller
{
public:
    Controller();
    ~Controller();
    void setActualDataString(std::string & actual_string) noexcept;
private:
    void waitAndSwapData() noexcept;
    void doWork() noexcept;
    std::chrono::steady_clock::time_point mTimeStamp;
    std::string mActualDataString;
    std::string mWorkedDataString;
    std::vector<std::vector<std::string>> mData;
    std::vector<std::vector<std::string>> mWorkedData;
    mutable std::mutex mDataStringMutex;
    mutable std::mutex mDataMutex;
    std::future<void> mWorkResult;
    std::atomic_bool mContinue;
};



}//namespace stc


#endif //INCLUDE_STC_CONTROLLER_HPP
