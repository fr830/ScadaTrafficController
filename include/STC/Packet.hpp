#ifndef INCLUDE_STC_PACKET_HPP
#define INCLUDE_STC_PACKET_HPP
#include <cstddef>
#include <vector>
#include <array>
#include <chrono>

namespace stc
{
namespace network
{

/*!
 * \brief The Packet class
 * \author Croessmah
 * \date 2018.07.01
 * \version 1.0
 *
 * Сетевой пакет.
 */
class Packet
{
public:
    using Data = std::vector<std::byte>;
    using Time = std::chrono::steady_clock::time_point;

    /*!
     * \brief Packet
     * \author Croessmah
     * \date 2018.07.01
     * \version 1.0
     * \param [in] sourceip ip-адрес устройства-отправителя
     * \param [in] destip ip-адрес устройства-получателя
     * \param [in] data данные, пришедшие в пакете
     *
     * Создает пакет с заданными параметрами
     */
    Packet(uint32_t sourceip, uint32_t destip,
           Data data, Time timestamp
           );

    /*!
     * \brief getSourceIP
     * \author Croessmah
     * \date 2018.07.01
     * \version 1.0
     * \return ip-адрес устройства-отправителя
     */
    uint32_t getSourceIP() const noexcept;

    /*!
     * \brief getDestIP
     * \author Croessmah
     * \date 2018.07.01
     * \version 1.0
     * \return ip-адрес устройства-получателя
     */
    uint32_t getDestIP() const noexcept;

    /*!
     * \brief getData
     * \author Croessmah
     * \date 2018.07.01
     * \version 1.0
     * \return lvalue-ссылку на вектор с данными
     *
     * Получение ссылки на данные пакета.
     */
    Data const & getData() const & noexcept;

    /*!
     * \brief перемещающая версия getData
     * \author Croessmah
     * \date 2018.07.01
     * \version 1.0
     * \return rvalue-ссылку на вектор с данными
     *
     * Получение ссылки на данные пакета. Вызывающий код может переместить данные из пакета.
     */
    Data && getData() && noexcept;
    Time getTimestamp() const noexcept;
    ~Packet();
private:
    uint32_t mSourceIP;
    uint32_t mDestIP;
    Data mData;
    Time mTimestamp;
};



}//namespace network
}//namespace stc

#endif //INCLUDE_STC_PACKET_HPP
