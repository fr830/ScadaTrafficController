#include <STC/Controller.hpp>


namespace stc
{

Controller::Controller()
{
    mContinue = true;
    mWorkResult = std::async(std::launch::async, [this]() { this->doWork(); });
}

Controller::~Controller()
{
    mContinue = false;
    mWorkResult.get();
}

void Controller::setActualDataString(std::string & actual_string) noexcept
{
    {
        std::lock_guard lock_actual_data_string(mDataStringMutex);
        actual_string.swap(mActualDataString);
    }
    mTimeStamp = std::chrono::steady_clock::now();
}

void Controller::waitAndSwapData() noexcept
{
    mWorkedDataString.clear();
    while (mContinue) {
        std::lock_guard lock_actual_data_string(mDataStringMutex);
        if (!mActualDataString.empty()) {
            mWorkedDataString.swap(mActualDataString);
            return;
        }
        std::this_thread::yield();
    }
}

void Controller::doWork() noexcept
{
    while (mContinue) {
        waitAndSwapData();

    }
}

}//namespace stc
