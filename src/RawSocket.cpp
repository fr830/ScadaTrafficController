#include <STC/RawSocket.hpp>
#include <STC/SafeAPI.hpp>
#include <STC/WSAGuard.hpp>
#include <ws2tcpip.h>

namespace
{

::stc::network::WSAGuard wsa_guard;

}//internal linkage


namespace stc
{
namespace network
{



RawSocket::RawSocket(uint32_t ip, int protocol):
    //Вызываем не делегирующий конструктор,
    //это обеспечит вызов деструктора в случае вылета исключения
    RawSocket()
{
    mSocket = socket(AF_INET, SOCK_RAW, protocol);
    if (mSocket == INVALID_SOCKET) {
        throw stc::Exception(stc::SafeGetLastError().second);
    }
    constexpr unsigned int HOSTNAME_LENGTH_MAX = 256;
    char host_name[HOSTNAME_LENGTH_MAX];
    if (gethostname(host_name, HOSTNAME_LENGTH_MAX)) {
        throw stc::Exception(stc::SafeGetLastError().second);
    }

    SOCKADDR_IN saddr;
    ZeroMemory(&saddr, sizeof(saddr));
    saddr.sin_family = AF_INET;
    saddr.sin_addr.s_addr = ip;

    int bind_result = bind(mSocket, reinterpret_cast<SOCKADDR*>(&saddr), sizeof(saddr));
    if (bind_result != NO_ERROR) {
        throw stc::Exception(stc::SafeGetLastError().second);
    }

    setReuse(true);
    setTimeout(1000 * 1);
    unsigned long flag = 1;

    if (ioctlsocket(mSocket, static_cast<long>(SIO_RCVALL), &flag)) {
        throw stc::Exception(stc::SafeGetLastError().second);
    }
}

RawSocket::RawSocket(RawSocket && src) noexcept:
    mSocket(src.mSocket)
{
    src.mSocket = INVALID_SOCKET;
}

RawSocket & RawSocket::operator=(RawSocket && src) noexcept
{
    if (this != &src) {
        close();
        mSocket = src.mSocket;
        src.mSocket = INVALID_SOCKET;
    }
    return *this;
}

RawSocket::~RawSocket() noexcept
{
    close();
}

SOCKET RawSocket::getSocket() const noexcept
{
    return mSocket;
}

//Инициализация значений по-умолчанию
//Используется в качестве не делегирующего конструктора
RawSocket::RawSocket() noexcept:
    mSocket(INVALID_SOCKET)
{
}

void RawSocket::close() noexcept
{
    if (mSocket != INVALID_SOCKET) {
        int close_result = closesocket(mSocket);
        mSocket = INVALID_SOCKET;
        if (close_result == SOCKET_ERROR) {
            //todo: log error
        }
    }
}

bool RawSocket::setTimeout(uint32_t msec)
{
    DWORD timeout = static_cast<DWORD>(msec);
    char const * data = reinterpret_cast<char const *>(&timeout);
    setsockopt(mSocket, SOL_SOCKET, SO_RCVTIMEO, data, sizeof(timeout));
    return true;
}

bool RawSocket::setReuse(bool state)
{
    int true_value = state;
    char const * data = reinterpret_cast<char const *>(&true_value);
    setsockopt(mSocket, SOL_SOCKET, SO_REUSEADDR, data, sizeof (true_value));
    return true;
}

}//namespace network
}//namespace stc
