#include <STC/DataPacket.hpp>
#include <tuple>
#include <algorithm>
#include <cstdlib>

namespace
{

//parse 123#some; fragment
//first - index (123)
//second, third - pointer to data ->some<-
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
    mPacket.reserve(300);//300 строк хватит кому угодно на любой пакет :)
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

bool DataPacket::isValid() const noexcept
{
    return mIndex != invalid_index;
}

bool DataPacket::parseFromString(std::string const & str)
{
    if (str.empty()) {
        return false;
    }
    uint32_t temporaryIndex = invalid_index;
    try {
        char const * begin = str.data();
        char const * end = str.data() + str.size();
        {
            [[maybe_unused]]
            auto[index, token_begin, token_end] = getTokenInfo(begin, end);
            begin = token_end + 1;
            if (index != 0) {
                return false;
            }
            char * num_end;
            unsigned long packet_index = strtoul(token_begin, &num_end, 10);
            if (num_end != token_end) {
                return false;
            }
            temporaryIndex = packet_index;
        }

        mIndex = invalid_index;
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
        mIndex = temporaryIndex;
    } catch (...) {
        mIndex = invalid_index;
        mPacket.clear();
        //todo: add other exception handlers
        return false;
    }

    return true;
}

void DataPacket::swap(DataPacket & src) noexcept
{
    if (this != &src) {
        std::swap(mIndex, src.mIndex);
        mPacket.swap(src.mPacket);
    }

}


}//namespace stc
