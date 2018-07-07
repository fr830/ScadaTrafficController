#ifndef INCLUDE_STC_RAWSOCKET_HPP
#define INCLUDE_STC_RAWSOCKET_HPP
#include <winsock2.h>//Ws2_32.lib
#include <cstdint>


namespace stc
{

namespace network
{

/*!
 * \brief Обертка для сырого сокета
 * \author Croessmah
 * \date 2018.06.29
 * \version 1.0
 *
 * Класс инкапсулирует создание, настройку и уничтожение сокета.
 * Создает статический объект stc::WSAGuard
 */
class RawSocket
{
public:
    /*!
     * \brief Конструктор
     * \param [in] ip IP-адрес устройства перехвата траффика
     * \param [in] protocol Протокол для захвата "сырым сокетом"
     *
     * Производит инициализацию и настройку сокета для захвата пакетов для устройства, заданного параметром
     */
    RawSocket(uint32_t ip, int protocol = IPPROTO_IP);

    /*!
     * \brief RawSocket move constructor
     * \param [in,out] src
     *
     * Перемещает сокет из входного параметра. Исходный сокет переходит в состояние INVALID_SOCKET.
     */
    RawSocket(RawSocket && src) noexcept;

    /*!
     * \brief RawSocket assignment operator
     * \param [in,out] src
     *
     * Перемещает сокет из входного параметра. Исходный сокет переходит в состояние INVALID_SOCKET.
     */
    RawSocket & operator=(RawSocket && src) noexcept;

    ~RawSocket() noexcept;

    RawSocket(RawSocket const &) = delete;
    RawSocket & operator=(RawSocket const &) = delete;

    /*!
     * \brief Возвращает копию значения SOCKET
     * \return возвращает сохраненный SOCKET
     *
     * Возвращает копию хранимого в объекте сокета
     */
    SOCKET getSocket() const noexcept;

    /*!
     * \brief Закрыть сокет
     *
     * Закрывает сокет
     */
    void close() noexcept;

    /*!
     * \brief Установить таймаут чтения
     * \param [in] msec количество миллисекунд
     * \return true в случае успеха
     *
     * Устанавливает таймаут дял операций с сокетом.
     */
    bool setTimeout(uint32_t msec);

private:
    bool setReuse(bool state);
    RawSocket() noexcept;
    SOCKET mSocket;
};

}//namespace network
}//namespace stc



#endif //INCLUDE_STC_RAWSOCKET_HPP
