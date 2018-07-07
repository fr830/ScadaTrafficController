#ifndef INCLUDE_STC_SNIFFEROPTIONS_HPP
#define INCLUDE_STC_SNIFFEROPTIONS_HPP
#include <cstdint>
#include <string>
#include <functional>
#include <cstddef>
#include <memory>

namespace stc
{

namespace network
{


class Acceptor;

class SnifferOptions
{
public:
    using AcceptorPointer = std::shared_ptr<Acceptor>;
    SnifferOptions();
    void loadFromFile(std::wstring filepath);
    void setAcceptor(AcceptorPointer acceptor);
    void setTimeout(uint32_t msec);
    void setIP(uint32_t ip);
    uint32_t getTimeout() const noexcept;
    uint32_t getIP() const noexcept;
    AcceptorPointer getAcceptor() const noexcept;
    ~SnifferOptions();
private:
    uint32_t mTimeout;
    uint32_t mIP;    
    AcceptorPointer mAcceptor;
};


}//namespace network
}//namespace stc



#endif //INCLUDE_STC_SNIFFEROPTIONS_HPP
