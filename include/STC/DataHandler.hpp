#ifndef INCLUDE_STC_DATAHANDLER_HPP
#define INCLUDE_STC_DATAHANDLER_HPP
#include <STC/DataEventsPool.hpp>
#include <memory>

namespace stc
{

void data_event_handler(std::shared_ptr<stc::DataEventsPool> events_pool);

}//namespace stc


#endif //INCLUDE_STC_DATAHANDLER_HPP
