#ifndef INCLUDE_STC_DATAPACKET_HPP
#define INCLUDE_STC_DATAPACKET_HPP
#include <STC/StaticString.hpp>
#include <vector>


namespace stc
{


class DataPacket
{
public:
    using DataString = stc::core::StaticString<7>;//8 bytes - 7 + '\0'
    using DataContainer = std::vector<DataString>;
    DataPacket(uint32_t index = invalid_index, DataContainer data = DataContainer()) noexcept;
    DataContainer const & getData() const noexcept;
    void setData(DataContainer data) noexcept;
    uint32_t getIndex() const noexcept;
    bool isValid() const noexcept;
    bool parseFromString(std::string const & str);
    void swap(DataPacket & src) noexcept;

    constexpr static uint32_t invalid_index = std::numeric_limits<uint32_t>::max();
private:

    DataContainer mPacket;
    uint32_t mIndex;
};


}//namespace stc


#endif //INCLUDE_STC_DATAPACKET_HPP
