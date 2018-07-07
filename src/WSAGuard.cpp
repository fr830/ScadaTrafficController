#include <winsock2.h>
#include "STC/WSAGuard.hpp"

namespace stc
{
namespace network
{

WSAGuard::WSAGuard()
{
    WSADATA mWSAData;
    int startup_result = WSAStartup(0x0202, &mWSAData);
    if (startup_result) {
        //todo: log
        throw 1;//todo: throw WSAException
    }
}

WSAGuard::~WSAGuard()
{
    if (WSACleanup()) {
        //todo: log
    }
}

}//namespace network
}//namespace stc
