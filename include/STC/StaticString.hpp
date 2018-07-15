#ifndef INCLUDE_STC_STATICSTRING_HPP
#define INCLUDE_STC_STATICSTRING_HPP
#include <cstdint>
#include <array>
#include <utility>
#include <cstdlib>
#include <cstring>

namespace stc
{

namespace core
{


template<std::size_t MaxSize>
class StaticString
{
    using ArrayType = std::array<char, MaxSize + 1>;
public:
    using Iterator = typename ArrayType::iterator;
    using ConstIterator = typename ArrayType::const_iterator;

    StaticString() noexcept:
        mSize(0)
    {
        mString[0] = '\0';
        mString[MaxSize] = '\0';
    }

    StaticString(char const * str) noexcept:
        mSize(0)
    {
        strcpy_s(mString.data(), mString.size(), str);
        mSize = strlen(mString.data());
        mString[MaxSize] = '\0';
    }

    StaticString(char const * str, char delim) noexcept:
        mSize(0)
    {
        while (mSize < MaxSize && *str && *str != delim ) {
            mString[mSize++] = *str;
        }
        mString[mSize] = '\0';
        mString[MaxSize] = '\0';
    }

    std::size_t size() const noexcept
    {
        return mSize;
    }

    constexpr std::size_t max_size() const noexcept
    {
        return MaxSize;
    }

    char const * c_str() const noexcept
    {
        return mString;
    }

    std::pair<long, Iterator> toLong(int radix = 10) const noexcept
    {
        char * pend;
        long number = std::strtol(mString.data(), &pend, radix);
        return {number, mString.begin() + (pend - mString.data())};
    }

    std::pair<double, Iterator> toDouble() const noexcept
    {
        char * pend;
        double number = std::strtod(mString.data(), &pend);
        return {number, mString.begin() + (pend - mString.data())};
    }
private:
    std::array<char, MaxSize + 1> mString;
    std::size_t mSize;
};



}//namespace core
}//namespace stc


#endif //INCLUDE_STC_STATICSTRING_HPP
