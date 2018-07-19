#include <STC/Controller.hpp>
#include <STC/IPv4Converter.hpp>
#include <cstring>
#include <cstdio>
#include <tuple>
#include <algorithm>



namespace stc
{

Controller::Controller(std::string const & name, std::string const & ip):
    mName(name),
    mIp(network::IPv4Converter(ip.c_str())),
    mSignal(true),
    mLastUpdate(TimeClock::now())
{
}

Controller::Controller(std::string const & name, uint32_t ip):
    mName(name),
    mIp(ip),
    mSignal(true),
    mLastUpdate(TimeClock::now())
{
}

Controller::~Controller()
{
}


std::string const & Controller::getName() const noexcept
{
    return mName;
}

uint32_t Controller::getIp() const noexcept
{
    return mIp;
}

void Controller::setActualPacket(DataPacket & packet)
{
    if (!packet.isValid()) {
        return;
    }
    size_t vec_index = packet.getIndex() / 10;
    std::lock_guard<std::mutex> locker(mDataMutex);

    if (vec_index >= mData.size()) {
        mData.resize(vec_index + 1);
    }
    mData[vec_index].swap(packet);
    mLastUpdate = TimeClock::now();
}

void Controller::setSignalState(bool state) noexcept
{
    mSignal = state;
}

bool Controller::isConnected() const noexcept
{
    return mSignal;
}

Controller::TimePoint Controller::getLastUpdate() const noexcept
{
    return mLastUpdate;
}



void Controller::getParameters(
        PackRequest const & param_info,
        PackResult & result
        ) const noexcept
{
    if (param_info.empty()) {
        return;
    }
    result.clear();
    result.reserve(param_info.size());
    std::lock_guard<std::mutex> locker(mDataMutex);
    for (auto [pac_index, val_index]: param_info) {
        uint32_t vec_index = pac_index / 10;
        if (vec_index < mData.size() &&
            val_index < mData[vec_index].getData().size()
            ) {
            result.emplace_back(pac_index,
                                val_index,
                                mData[vec_index].getData()[val_index]
                                );
        }
    }
}



}//namespace stc
