#include <memory>
#include <string>
#include <tuple>

#include <iomanip> //todo: delete this include
#include <iostream> //todo: delete this include
#include <sstream> //todo: delete this include

#include <thread>
#include <STC/RawSocket.hpp>
#include <STC/SafeAPI.hpp>
#include <STC/Packet.hpp>
#include <STC/Sniffer.hpp>
#include <STC/SnifferOptions.hpp>
#include <STC/FilteredIPv4Acceptor.hpp>
#include <STC/IPv4Header.hpp>
#include <STC/TCPAcceptor.hpp>
#include <STC/ControllerAcceptor.hpp>
#include <STC/Controller.hpp>
#include <STC/DataEventsPool.hpp>

#include <iphlpapi.h>



std::vector<stc::network::FilterIPv4Options>
make_controllers_tcp_filter(
        std::vector<std::shared_ptr<stc::Controller>> & controllers,
        std::shared_ptr<stc::DataEventsPool> events_pool
        )
{
    std::vector<stc::network::FilterIPv4Options> result;
    for (auto & controller: controllers) {
        result.emplace_back(
            std::make_shared<::stc::network::TCPAcceptor>(
                std::make_shared<stc::ControllerAcceptor>(
                            controller,
                            std::move(events_pool)
                            )
                ),
            controller->getIp(),
            stc::network::FilterIPv4Options::Protocol::TCP
            );
    }
    return result;
}




int main()
{
    try {
        auto info_ptr = stc::SafeGetAdaptersInfo();

        PIP_ADAPTER_INFO adapter_info = info_ptr.get();

        while (adapter_info) {
            std::cout << "Adapter\n";
            std::cout << "\tName: " << adapter_info->AdapterName << std::endl;
            std::cout << "\tDescription: " << adapter_info->Description << std::endl;

            std::cout << "\tMAC: " << std::hex;
            for (unsigned i = 0; i < adapter_info->AddressLength; ++i) {
                std::cout << (i?".":"") << static_cast<unsigned>(adapter_info->Address[i]);
            }

            std::cout << std::dec << std::endl;

            std::cout << "\tCurrent IP: " << adapter_info->IpAddressList.IpAddress.String << std::endl;


            adapter_info = adapter_info->Next;
        }


    } catch (stc::Exception const & e) {
        std::wcout << e.message() << std::endl;
    } /*catch (...) {
        std::cout << "catch" << std::endl;
    }*/

    std::shared_ptr<stc::DataEventsPool> events_pool =
            std::make_shared<stc::DataEventsPool>();



    std::vector<std::shared_ptr<stc::Controller>> controllers{
        std::make_shared<stc::Controller>("ft5p", "192.168.0.111"),
        std::make_shared<stc::Controller>("srgm", "192.168.0.112")
    };

    std::thread worker(
                [events_pool]() {
                    stc::Event event;
                    events_pool->waitEvent(event);
                    while (event.mType != stc::EventType::Close) {
                        bool has_event = true;
                        while(has_event && event.mType != stc::EventType::Close) {
                            has_event = events_pool->popEvent(event);

                            switch (event.mType) {
                            case stc::EventType::Update:
                                std::cout << "Controller: ";
                                std::cout << std::get<1>(event.mData).first->getName() << "\n";
                                std::cout << std::get<1>(event.mData).second << "\n\n";
                                break;
                            default:
                                std::cout << (int)event.mType << std::endl;
                            }

                        }
                        events_pool->waitEvent(event);
                    }
                }
        );
    worker.detach();

    auto ip_filter_list =  make_controllers_tcp_filter(controllers, events_pool);

    stc::network::SnifferOptions opt;

    opt.setAcceptor(
                std::make_shared<stc::network::FilteredIPv4Acceptor>(
                    std::move(ip_filter_list)
                    )
    );

    opt.setIP(inet_addr("192.168.0.110"));

    stc::network::Sniffer sniffer;

    sniffer.start(opt);

    return EXIT_SUCCESS;
}


/*
#include <codecvt>



int
main()
{
    service_logger_init("a/Test.log");
    log4cplus::Logger & test = get_service_logger();
    log4cplus::Logger test2 = get_service_logger();
    for (int i = 0; i < 102400; ++i) {
        LOG4CPLUS_DEBUG(test, LOG4CPLUS_TEXT("this русский текст печатается? is log message with number ") << i);
        LOG4CPLUS_FATAL(test2, LOG4CPLUS_TEXT("rus?"));

    }

    stc::Logger logService(stc::LoggerOptions::make_file_options("file.log", 1024 * 1024, 3));
    stc::Logger logSniffer(stc::LoggerOptions::make_file_options("file.log", 1024 * 1024, 3));
    stc::Logger::logService.warning("Warning");
    return 0;
}
*/
