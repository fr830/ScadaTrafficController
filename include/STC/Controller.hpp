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
    using ActualData= std::vector<std::vector<std::string>>;
    Controller();
    ~Controller();
    void setActualDataString(std::string & actual_string) noexcept;
    void getActualData(ActualData & out_data) noexcept;
private:
    void waitAndSwapData() noexcept;
    void doWork() noexcept;
    std::chrono::steady_clock::time_point mTimeStamp;
    std::string mActualDataString;
    std::string mWorkedDataString;
    ActualData mData;
    ActualData mWorkedData;
    mutable std::mutex mDataStringMutex;
    mutable std::mutex mDataMutex;
    std::future<void> mWorkResult;
    std::atomic_bool mContinue;
};



}//namespace stc


#endif //INCLUDE_STC_CONTROLLER_HPP
