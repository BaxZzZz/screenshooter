#include <atomic>
#include <thread>

#include "process/signal_handler.h"

namespace process
{

const std::size_t WAIT_TIMEOUT = 5000;

namespace
{

std::atomic<bool> IS_RUNNING { true };

void signal_handler(int /*signal_number*/)
{
    IS_RUNNING = false;
}

} // namespace

void signal_register(const signal_array& signals)
{
    for (auto signal_number : signals)
    {
        signal(signal_number, signal_handler);
    }
}

void wait_signals()
{
    while (IS_RUNNING)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(WAIT_TIMEOUT));
    }
}

} // namespace process
