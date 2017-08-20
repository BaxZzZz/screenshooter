#ifndef PROCESS_SIGNAL_HANDLER_H
#define PROCESS_SIGNAL_HANDLER_H

#include <csignal>
#include <vector>
#include <functional>

namespace process
{

using signal_array = std::vector<int>;

void signal_register(const signal_array& signals);

void wait_signals();

} // namespace system

#endif // PROCESS_SIGNAL_HANDLER_H
