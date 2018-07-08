#include <STC/TCPAcceptor.hpp>

namespace stc
{
namespace network
{

TCPAcceptor::TCPAcceptor(std::shared_ptr<Acceptor> acceptor):
    mAcceptor(std::move(acceptor))
{
}

void TCPAcceptor::accept(std::byte const * ptr, uint32_t size) noexcept
{
    TCPHeader const * header = reinterpret_cast<TCPHeader const *>(ptr);
    if (header->mFIN || header->mRST || header->mSYN) {
        resetPacketData();
        return;
    }
    if (!mHeader.has_value()) {
        mHeader = *header;
        mData.clear();
    }
    if (header->mACK && header->mAckSn == mHeader.value().mAckSn) {
        uint32_t data_offset = header->mDataOffset * 4;
        uint32_t data_size = size - data_offset;
        size_t old_size = mData.size();
        mData.resize(old_size + data_size);
        memcpy(mData.data() + old_size, ptr + data_offset, data_size);
        if (header->mPSH) {
            mAcceptor->accept(mData.data(), mData.size());
            resetPacketData();
        }
    } else {
        resetPacketData();
    }
}

void TCPAcceptor::resetPacketData() noexcept
{
    mData.clear();
    mHeader.reset();
}


}//namespace network
}//namespace stc
