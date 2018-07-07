#ifndef INCLUDE_STC_IPV4HEADER_HPP
#define INCLUDE_STC_IPV4HEADER_HPP


#include <cstdint>
namespace stc
{
namespace network
{

//todo: engian class
struct IPv4Header final
{
    uint8_t mHeaderSize: 4;//Header size in 32-bit word/ min 5
    uint8_t mIpVersion: 4;//Protocol version
    uint8_t mECN: 2;//Explicit Congestion Notification
    uint8_t mDSCP: 6;//Differentiate Services Code Point
    uint16_t mTotalLength;//Size of packet
    uint16_t mId;//Packet identifier
    uint8_t mOffset1: 5;//Data offest (part one)
    uint8_t mMF: 1;//more fragment
    uint8_t mDF: 1;//do not fragment
    uint8_t mReservedFlag: 1;//Reserved. Must be equal zero
    uint8_t mOffset2;//Data offset (part two)
    uint8_t mTTL;//Packet lifetime
    uint8_t mProtocol;//Protocol type
    uint16_t mCRC16;//CRC16
    uint32_t mSourceIP;//Source IP address
    uint32_t mDestinationIP;//Destination IP address
};


}//namespace network
}//namespace stc

#endif //INCLUDE_STC_IPV4HEADER_HPP
