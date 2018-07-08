#include <memory>
#include <string>

#include <iomanip> //todo: delete this include
#include <iostream> //todo: delete this include

#include <thread>
#include <STC/RawSocket.hpp>
#include <STC/SafeAPI.hpp>
#include <STC/Packet.hpp>
#include <STC/Sniffer.hpp>
#include <STC/SnifferOptions.hpp>
#include <STC/FilteredIPv4Acceptor.hpp>
#include <STC/IPv4Header.hpp>
#include <STC/TCPAcceptor.hpp>

#include <iphlpapi.h>




class MyAccepter:
        public stc::network::Acceptor
{
    std::string mName;
public:
    MyAccepter(std::string acceptor_name):
        mName(acceptor_name)
    {
    }
    void accept(std::byte const * ptr, uint32_t size) noexcept override
    {
        char const * data_begin = reinterpret_cast<char const *>(ptr);
        char const * data_end = reinterpret_cast<char const *>(ptr) + size;
        auto is_null = [](char b) { return !b; };
        data_begin = std::find_if_not(data_begin, data_end, is_null);
        data_end = std::find_if(data_begin, data_end, is_null);
        (std::cout << "NEW PACKET FOR " << mName << ": \n" << std::string(data_begin, data_end) << "\n\n").flush();
    }
};



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

    std::shared_ptr<stc::network::Acceptor> my_acceptor_dryer(std::make_shared<MyAccepter>("DRYER"));
    std::shared_ptr<stc::network::Acceptor> my_acceptor_gener(std::make_shared<MyAccepter>("GENERATOR"));

    std::shared_ptr<stc::network::Acceptor> tcp_acceptor_dryer(std::make_shared<::stc::network::TCPAcceptor>(my_acceptor_dryer));
    std::shared_ptr<stc::network::Acceptor> tcp_acceptor_gener(std::make_shared<::stc::network::TCPAcceptor>(my_acceptor_gener));

    std::vector<stc::network::FilterIPv4Options> ip_filter_list{
        stc::network::FilterIPv4Options(tcp_acceptor_dryer, "192.168.0.111", stc::network::FilterIPv4Options::Protocol::TCP),
        stc::network::FilterIPv4Options(tcp_acceptor_gener, "192.168.0.112", stc::network::FilterIPv4Options::Protocol::TCP),
    };

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
