#ifndef PROCESS_SIGNAL_HANDLER_H
#define PROCESS_SIGNAL_HANDLER_H

#include <csignal>
#include <vector>
#include <functional>

namespace process
{

/*!
 * \brief Array of signal numbers
 */
using signal_array = std::vector<int>;

/*!
 * \brief Function for registation of handling signal numbers
 */
void signal_register(const signal_array& signals);

/*!
 * \brief Function waiting for signals arrival
 */
void wait_signals();

} // namespace system

#endif // PROCESS_SIGNAL_HANDLER_H
