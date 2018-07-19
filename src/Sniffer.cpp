#include <STC/Sniffer.hpp>
#include <STC/SnifferOptions.hpp>
#include <STC/RawSocket.hpp>
#include <STC/Exception.hpp>
#include <STC/Acceptor.hpp>
#include <atomic>
#include <vector>
#include <cstddef>
#include <thread>
#include <algorithm>
#include <cstring>

namespace stc
{
namespace network
{


Sniffer::Sniffer():
    mRunning(false)
{
}

bool Sniffer::start(SnifferOptions options)
{
    mRunning.store(true);
    while (mRunning) {
        try {
            SnifferOptions::AcceptorPointer acceptor = options.getAcceptor();
            if (!acceptor) {
                return false;
            }
            stc::network::RawSocket rs(options.getIP());
            constexpr size_t buffer_length = 1024 * 64;
            std::byte buffer[buffer_length];
            SOCKADDR_IN saddr;
            int size_saddr = sizeof(saddr);
            while (mRunning.load()) {
                int recv_result = recvfrom(
                  rs.getSocket(),
                  reinterpret_cast<char *>(buffer),
                  buffer_length,
                  0,
                  reinterpret_cast<SOCKADDR *>(&saddr),
                  &size_saddr
                );

                if (recv_result == 0) {
                    break;
                }

                if (recv_result == SOCKET_ERROR) {
                    acceptor->timeout();
                    break;
                }

                uint32_t size_in_bytes = static_cast<uint32_t>(recv_result);
                acceptor->accept(buffer, size_in_bytes);
            }
        } catch (stc::Exception const & e) {
            //todo: log
            (void)e;
        } catch (std::exception const & e) {
            //todo: log
            (void)e;
        } catch (...) {
            //todo: log
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void Sniffer::stop()
{
    mRunning.store(false);
}

Sniffer::~Sniffer()
{

}


}//namespace network
}//namespace stc



