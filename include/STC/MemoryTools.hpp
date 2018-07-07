#ifndef INCLUDE_STC_MEMORYTOOLS_HPP
#define INCLUDE_STC_MEMORYTOOLS_HPP

#include <cstdlib>
#include <stdexcept>

namespace stc
{

/*!
 * \brief Выделение буфера памяти
 * \author Croessmah
 * \date 2018.06.29
 * \version 1.0
 * \param size - размер выделяемого буфера в байтах
 * \return указатель на выделенную память
 * \throw std::bad_alloc в случае ошибки выделения памяти
 *
 * Выделяет буфер памяти заданного размера
 */
void * alloc_buffer(size_t size);

/*!
 * \brief Уничтожение буфера памяти
 * \author Croessmah
 * \date 2018.06.29
 * \version 1.0
 * \param ptr - указатель на память, выделенную функцией alloc_buffer
 *
 * Уничтожает буфер памяти, ранее выделенный функцией alloc_buffer
 */
void free_buffer(void * ptr);


/*!
 * \brief The BufferDeletor class
 * \author Croessmah
 * \date 2018.06.29
 * \version 1.0
 *
 * Функтор для освобождения памяти, выделенной с помощью alloc_buffer.
 * Реализован для использования в качестве delete'ра в unique_ptr.
 */
struct BufferDeletor
{
    /*!
     * \brief Шаблонный operator()
     * \author Croessmah
     * \date 2018.06.29
     * \version 1.0
     *
     * Вызывает stc::free_buffer для освобождения памяти
     */
    template<typename T>
    void operator()(T * p)
    {
        ::stc::free_buffer(p);
    }
};



}



#endif // INCLUDE_STC_MEMORYTOOLS_HPP
