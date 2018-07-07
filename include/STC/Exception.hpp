#ifndef INCLUDE_STC_EXCEPTION_HPP
#define INCLUDE_STC_EXCEPTION_HPP

#include <string>
#include <exception>

namespace stc
{


/*!
 * \brief The Exception class
 *
 * Базовый класс для всех исключений проекта, кроме исключений, выбрасываемых стандартной библиотекой C++
 *
 * \author Croessmah
 * \date 2018.06.29
 * \version 1.0
 */
class Exception
{
public:
    /*!
     * \brief Конструктор
     * \param [in] msg Сохраняемое сообщение об ошибке
     * \throw std::bad_alloc В случае возникновения ошибки при выделении памяти
     *
     * Конструктор, сохраняющий переданное сообщение
     */
    Exception(std::wstring msg);
    /*!
     * \brief Виртуальный деструктор
     *
     * Виртуальный деструктор
     */
    virtual ~Exception();
    /*!
     * \brief Получение сообщения
     * \return Возвращает указатель на нуль-терминированную строку широких символов
     *
     * Возвращает сохраненное сообщение
     */
    virtual wchar_t const * message() const noexcept;
protected:
    std::wstring mMessage;
};


}//namespace stc


#endif //INCLUDE_STC_EXCEPTION_HPP
