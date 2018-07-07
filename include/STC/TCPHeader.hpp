#ifndef INCLUDE_STC_TCPHEADER_HPP
#define INCLUDE_STC_TCPHEADER_HPP
#include <cstdint>

namespace stc
{
namespace network
{


struct __attribute((packed)) TCPHeader final
{
    uint16_t mSourcePort;
    uint16_t mDestinationPort;
    uint32_t mSeqNumber;
    uint32_t mAckSn;

    uint8_t mReserved1: 4;
    uint8_t mDataOffset: 4;

    uint8_t mFIN: 1;
    uint8_t mSYN: 1;
    uint8_t mRST: 1;
    uint8_t mPSH: 1;
    uint8_t mACK: 1;
    uint8_t mURG: 1;
    uint8_t mReserved2: 2;

    uint16_t mWindowSize;
    uint16_t mCRC16;
    uint16_t mUrgPtr;
};


}//namespace network
}//namaspace stc

#endif //INCLUDE_STC_TCPHEADER_HPP
