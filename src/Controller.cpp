#include <STC/Controller.hpp>
#include <cstring>
#include <cstdio>
#include <tuple>
#include <algorithm>

namespace
{


std::string::const_iterator parse_next_int(std::string::const_iterator begin,
                                           std::string::const_iterator end,
                                           int & result)
{
    result = 0;
    while (begin != end && *begin >= '0' && *begin <='9') {
        result *= 10;
        result += *begin - '0';
        ++begin;
    }
    return begin;
}


std::tuple<int, std::string::const_iterator, std::string::const_iterator>
parse_next(
        std::string::const_iterator begin,
        std::string::const_iterator end
        )
{
    int index = 0;
    auto safe_begin = begin;
    begin = parse_next_int(begin, end, index);
    if (begin == safe_begin || begin == end || *begin != '#') {
        throw 1;//todo: ошибка формата
    }
    safe_begin = ++begin;
    begin = std::find(begin, end, ';');
    if (begin == end || begin == safe_begin) {
        throw 2;//todo: ошибка формата
    }
    std::tuple<int, std::string::const_iterator, std::string::const_iterator> result;
    std::get<0>(result) = index;
    std::get<1>(result) = safe_begin;
    std::get<2>(result) = begin;
    return result;
}


void parse_to_vector(
        std::string::const_iterator current,
        std::string::const_iterator end,
        std::vector<std::string> & result
        )
{
    while (current != end) {
        auto[index, value_begin, value_end] = parse_next(current, end);
        current = value_end + 1;
        unsigned u_index = static_cast<unsigned>(index);
        if (u_index >= result.size()) {
            result.resize(u_index + 1);
        }
        result[u_index].assign(value_begin, value_end);
    }
}


std::string::const_iterator get_packet_index(std::string::const_iterator begin,
                                              std::string::const_iterator end,
                                              unsigned & result)
{
    auto[packet_index_raw, index_begin, index_end] = parse_next(begin, end);
    parse_next_int(index_begin, index_end, packet_index_raw);
    result = static_cast<unsigned>(packet_index_raw /= 10);
    return ++index_end;
}

}//internal linkage



namespace stc
{

Controller::Controller()
{
    mContinue = true;
    mWorkResult = std::async(std::launch::async, [this]() { this->doWork(); });
}

Controller::~Controller()
{
    mContinue = false;
    mWorkResult.get();
}

void Controller::setActualDataString(std::string & actual_string) noexcept
{
    std::lock_guard lock_actual_data_string(mDataStringMutex);
    actual_string.swap(mActualDataString);
    mTimeStamp = std::chrono::steady_clock::now();
}

void Controller::getActualData(Controller::ActualData & out_data) noexcept
{
    std::lock_guard lock_data(mDataMutex);
    out_data.swap(mData);
}

bool Controller::isRunning() const noexcept
{
    return mContinue;
}

void Controller::waitAndSwapData() noexcept
{
    mWorkedDataString.clear();
    while (mContinue) {
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        std::lock_guard lock_actual_data_string(mDataStringMutex);
        if (!mActualDataString.empty()) {
            mWorkedDataString.swap(mActualDataString);
            return;
        }
        //todo: добавить учет долгого отсутствия данных
    }
}

void Controller::doWork() noexcept
{
    while (mContinue) {
        waitAndSwapData();//блокирует поток до прихода данных
        if (mWorkedDataString.front() != '<' ||
            mWorkedDataString.back()  != '>'
            ) {
            continue;
        }
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
}

}//namespace stc
