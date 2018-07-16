#ifndef INCLUDE_STC_CONTROLLER_HPP
#define INCLUDE_STC_CONTROLLER_HPP

#include <string>
#include <vector>
#include <mutex>
#include <atomic>
#include <future>

namespace stc
{


class Controller
{
public:
    using ActualData = std::vector<std::vector<std::string>>;
    Controller(std::string const & name, std::string const & ip);
    Controller(std::string const & name, uint32_t ip);
    ~Controller();
    void getActualData(ActualData & out_data) const noexcept;
    std::string const & getName() const noexcept;
    uint32_t getIp() const noexcept;
private:
    std::string mName;
    uint32_t mIp;
    ActualData mData;
    mutable std::mutex mDataMutex;
};



}//namespace stc


#endif //INCLUDE_STC_CONTROLLER_HPP
