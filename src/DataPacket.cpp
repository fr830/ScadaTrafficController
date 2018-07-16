#include <STC/DataPacket.hpp>
#include <tuple>
#include <algorithm>
#include <type_traits>

namespace
{


std::tuple<unsigned long, char const *, char const *>
getTokenInfo (char const * begin, char const * end)
{
    std::tuple<unsigned long, char const *, char const *> result;
    char * stop_pos = nullptr;
    unsigned long index = strtoul(begin, &stop_pos, 10);
    if (stop_pos == end || *stop_pos != '#') {
        throw std::invalid_argument("invalid package string format");//todo other error type
    }
    ++stop_pos;
    char const * token_end = std::find(
                const_cast<char const *>(stop_pos),
                end,
                ';'
                );
    if (token_end == end) {
        throw std::invalid_argument("invalid package string format");//todo other error type
    }
    std::get<0>(result) = index;
    std::get<1>(result) = stop_pos;
    std::get<2>(result) = token_end;
    return result;

}


}//internal linkage


namespace stc
{



DataPacket::DataPacket(uint32_t index, DataContainer data) noexcept:
    mPacket(std::move(data)),
    mIndex(index)
{
}

DataPacket::DataContainer const & DataPacket::getData() const noexcept
{
    return mPacket;
}

void DataPacket::setData(DataContainer data) noexcept
{
    mPacket = std::move(data);
}

uint32_t DataPacket::getIndex() const noexcept
{
    return mIndex;
}

bool DataPacket::parseFromString(std::string const & str)
{
    if (str.empty()) {
        return false;
    }

    char const * begin = str.data();
    char const * end = str.data() + str.size();
    {
        [[maybe_unused]]
        auto[packet_index, unused_begin, token_end] = getTokenInfo(begin, end);
        begin = token_end + 1;
        mIndex = packet_index;
    }
    mPacket.clear();
    while (begin != end) {
        auto[val_index, token_begin, token_end] = getTokenInfo(begin, end);

        if (val_index == mPacket.size()) {
            mPacket.emplace_back(token_begin, token_end);
        } else {
            if (val_index > mPacket.size()) {
                mPacket.reserve(val_index + 10);
                mPacket.resize(val_index + 1);
            }
            mPacket.emplace(mPacket.begin() + static_cast<ptrdiff_t>(val_index),
                            token_begin,
                            token_end
                            );
        }
        begin = token_end + 1;
    }
}


}//namespace stc
