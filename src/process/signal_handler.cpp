#include <atomic>
#include <thread>

#include "process/signal_handler.h"

namespace process
{

namespace
{

std::atomic<bool> IS_RUNNING { true };

void signal_callback(int /*signal_number*/)
{
    IS_RUNNING = false;
}

} // namespace

signal_handler::signal_handler(const signal_array& signals)
{
    for (auto signal_number : signals)
    {
        signal(signal_number, signal_callback);
    }
}

void signal_handler::wait()
{
    while (IS_RUNNING)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    }
}

} // namespace process
