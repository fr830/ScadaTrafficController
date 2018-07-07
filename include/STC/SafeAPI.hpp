#ifndef INCLUDE_STC_SAFEAPI_HPP
#define INCLUDE_STC_SAFEAPI_HPP

#include <memory>
#include <string>
#include <windows.h>
#include <utility>
#include <STC/Exception.hpp>
#include <STC/MemoryTools.hpp>

typedef struct _IP_ADAPTER_INFO IP_ADAPTER_INFO;
namespace stc
{

/*!
 * \brief SafeGetAdaptersInfo
 * \author Croessmah
 * \date 2018.06.28
 * \version 1.0
 * \return Возвращает умный указатель на структуру IP_ADAPTER_INFO
 *
 * Функция получает информацию о сетевых адаптерах с помощью GetAdaptersInfo
 */
std::unique_ptr<IP_ADAPTER_INFO, ::stc::BufferDeletor> SafeGetAdaptersInfo();


/*!
 * \brief SafeGetLastError
 * \author Croessmah
 * \date 2018.06.28
 * \version 1.0
 * \param [in] generate_text Если не задан, то текст ошибки не генерируется
 * \return Возвращает пару значений. first - код ошибки, second - текст ошибки, если установлен generate_text
 *
 * Функция получает информацию о последней произошедшей ошибке
 */
std::pair<DWORD, std::wstring> SafeGetLastError(bool generate_text = true);


/*
  Exception classes
*/


/*!
 * \brief The AdaptersInfoFailure class
 * \author Croessmah
 * \date 2018.06.28
 * \version 1.0
 *
 * Исключение для ошибок функции GetAdaptersInfo
 */
class AdaptersInfoFailure:
        public stc::Exception
{
    using stc::Exception::Exception;
};

/*!
 * \brief The FormatMessageFailure class
 * \author Croessmah
 * \date 2018.06.28
 * \version 1.0
 *
 * Исключение для ошибок функции FormatMessage
 */
class FormatMessageFailure:
        public stc::Exception
{
    using stc::Exception::Exception;
};


}//namespace stc


#endif // INCLUDE_STC_SAFEAPI_HPP
