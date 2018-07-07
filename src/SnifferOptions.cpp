#include <STC/SnifferOptions.hpp>
#include <STC/Acceptor.hpp>

namespace stc
{
namespace network
{


SnifferOptions::SnifferOptions()
{
    //todo: def init
}

void SnifferOptions::setAcceptor(SnifferOptions::AcceptorPointer acceptor)
{
    mAcceptor = acceptor;
}


void SnifferOptions::setIP(uint32_t ip)
{
    mIP = ip;
}

uint32_t SnifferOptions::getTimeout() const noexcept
{
    return mTimeout;
}

uint32_t SnifferOptions::getIP() const noexcept
{
    return mIP;
}

SnifferOptions::~SnifferOptions()
{
}

SnifferOptions::AcceptorPointer SnifferOptions::getAcceptor() const noexcept
{
    return mAcceptor;
}


void SnifferOptions::setTimeout(uint32_t msec)
{
    mTimeout = msec;
}


}//namespace network
}//namespace stc

