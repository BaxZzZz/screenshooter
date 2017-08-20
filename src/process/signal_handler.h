#ifndef PROCESS_SIGNAL_HANDLER_H
#define PROCESS_SIGNAL_HANDLER_H

#include <csignal>
#include <vector>
#include <functional>

namespace process
{

class signal_handler
{

public:

    using signal_array = std::vector<int>;

public:

    signal_handler(const signal_array& signals);

    void wait();

};

} // namespace system

#endif // PROCESS_SIGNAL_HANDLER_H
