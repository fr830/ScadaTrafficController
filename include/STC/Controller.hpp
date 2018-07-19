#ifndef INCLUDE_STC_CONTROLLER_HPP
#define INCLUDE_STC_CONTROLLER_HPP

#include <string>
#include <vector>
#include <mutex>
#include <atomic>
#include <chrono>
#include <STC/DataPacket.hpp>

namespace stc
{





class Controller
{
public:
    using TimeClock = std::chrono::steady_clock;
    using TimePoint = TimeClock::time_point;
    using ActualData = std::vector<DataPacket>;
    using PackRequest = std::vector<std::pair<uint32_t, uint32_t>>;
    using PackResult = std::vector<std::tuple<uint32_t, uint32_t, DataPacket::DataString>>;
    Controller(std::string const & name, std::string const & ip);
    Controller(std::string const & name, uint32_t ip);
    ~Controller();
    std::string const & getName() const noexcept;
    uint32_t getIp() const noexcept;
    void setActualPacket(DataPacket & packet);
    void setSignalState(bool state) noexcept;
    bool isConnected() const noexcept;
    TimePoint getLastUpdate() const noexcept;

    void getParameters(
            PackRequest const & param_info,
            PackResult & result
            ) const noexcept;
private:
    std::string mName;
    uint32_t mIp;
    ActualData mData;
    mutable std::mutex mDataMutex;
    std::atomic_bool mSignal;
    std::atomic<TimePoint> mLastUpdate;
};



}//namespace stc


#endif //INCLUDE_STC_CONTROLLER_HPP
