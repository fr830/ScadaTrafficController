#include <STC/Packet.hpp>


namespace stc
{
namespace network
{


Packet::Packet(uint32_t sourceip, uint32_t destip,
               Data data, Time timestamp):
    mSourceIP(sourceip),
    mDestIP(destip),
    mData(std::move(data)),
    mTimestamp(timestamp)
{
}

uint32_t Packet::getSourceIP() const noexcept
{
    return mSourceIP;
}

uint32_t Packet::getDestIP() const noexcept
{
    return mDestIP;
}

Packet::Data const & Packet::getData() const & noexcept
{
    return mData;
}

Packet::Data && Packet::getData() && noexcept
{
    return std::move(mData);
}

Packet::Time Packet::getTimestamp() const noexcept
{
    return mTimestamp;
}



}//namespace network
}//namespace stc

