#ifndef INCLUDE_STC_WSAGUARD_HPP
#define INCLUDE_STC_WSAGUARD_HPP


namespace stc
{
namespace network
{

/*!
 * \brief Обертка над WSADATA
 * \author Croessmah
 * \date 2018.06.29
 * \version 1.0
 *
 * Класс управляет объектом WSADATA
 */
class WSAGuard
{
public:
    WSAGuard(WSAGuard const &) = delete;
    WSAGuard & operator=(WSAGuard const &) = delete;
    WSAGuard();
    ~WSAGuard();
};

}//namespace network
}//namespace stc


#endif // INCLUDE_STC_WSAGUARD_HPP
