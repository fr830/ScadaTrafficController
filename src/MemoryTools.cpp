#include "STC/MemoryTools.hpp"


namespace stc
{

void * alloc_buffer(size_t size)
{
    return new unsigned char[size];
}

void free_buffer(void * ptr)
{
    delete [] static_cast<unsigned char *>(ptr);
}


}//namespace stc

