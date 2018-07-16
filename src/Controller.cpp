#include <STC/Controller.hpp>
#include <STC/IPv4Converter.hpp>
#include <cstring>
#include <cstdio>
#include <tuple>
#include <algorithm>



namespace stc
{

Controller::Controller(std::shared_ptr<DataEventsPool> events_pool, std::string const & name, std::string const & ip):
    mEventsPool(events_pool),
    mName(name),
    mIp(network::IPv4Converter(ip.c_str()))
{
    if (!mEventsPool) {
        throw std::logic_error("Events pool is null");
    }
}

Controller::Controller(std::shared_ptr<DataEventsPool> events_pool, std::string const & name, uint32_t ip):
    mEventsPool(events_pool),
    mName(name),
    mIp(ip)
{
    if (!mEventsPool) {
        throw std::logic_error("Events pool is null");
    }
}

Controller::~Controller()
{
}


void Controller::getActualData(Controller::ActualData & out_data) const noexcept
{
    std::lock_guard lock_data(mDataMutex);
    out_data = mData;
}

std::shared_ptr<DataEventsPool> Controller::getEventsPool() const noexcept
{
    return mEventsPool;
}

std::string const & Controller::getName() const noexcept
{
    return mName;
}

uint32_t Controller::getIp() const noexcept
{
    return mIp;
}


/*void Controller::doWork() noexcept
{
    while (mContinue) {
        waitAndSwapData();//блокирует поток до прихода данных
        auto current = mWorkedDataString.cbegin() + 1;
        auto end = mWorkedDataString.cend() - 1;

        try {
            unsigned packet_index;
            current = get_packet_index(current, end, packet_index);
            if (packet_index >= mWorkedData.size()) {
                mWorkedData.resize(packet_index + 1);
            }
            auto & vec = mWorkedData[packet_index];
            parse_to_vector(current, end, vec);
            std::lock_guard lock_data(mDataMutex);
            if (packet_index >= mData.size()) {
                mData.resize(packet_index + 1);
            }
            mData[packet_index].swap(vec);
        } catch (...) {
            //todo: добавить в лог информацию о битом пакете
        }
    }
}*/

}//namespace stc
