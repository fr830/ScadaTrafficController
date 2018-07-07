#ifndef INCLUDE_STC_SNIFFER_HPP
#define INCLUDE_STC_SNIFFER_HPP
#include <memory>
#include <atomic>

namespace stc
{
namespace network
{

class RawSocket;
class SnifferOptions;


/*!
 * \brief The Sniffer class
 * \author Croessmah
 * \date 2018.06.30
 * \version 1.0
 *
 * Класс, реализующий захват пакетов и их фильтрацию.
 */
class Sniffer
{
public:
    /*!
     * \brief Конструктор
     * \author Croessmah
     * \date 2018.06.30
     * \version 1.0
     *
     * Конструктор инициализирует сниффер. Не начинает захват траффика.
     */
    Sniffer();

    /*!
     * \brief Запуск захвата пакетов
     * \author Croessmah
     * \date 2018.06.30
     * \version 1.0
     * \param [in] options Настройки сниффера
     * \return true если захват был завершен без ошибок
     *
     * Функция захвата пакетов. Блокирует поток исполнения.
     */
    bool start(SnifferOptions options);

    /*!
     * \brief Прекращение захвата
     *
     * Останавливает захват пакетов. При этом start возвращает true.
     */
    void stop();

    ~Sniffer();
private:
    std::atomic_bool mRunning;
};


}//namespace network
}//namespace stc


#endif //INCLUDE_STC_TCPSNIFFER_HPP
