#include <sys/stat.h>
#include <unistd.h>

#include "process/daemonizer.h"

namespace process
{

bool daemonize()
{
    auto pid = fork();

    if (pid == -1)
    {
        return false;
    }

    if (!pid)
    {
        umask(0);
        setsid();
        chdir("/");
        close(STDIN_FILENO);
        close(STDOUT_FILENO);
        close(STDERR_FILENO);
        return true;
    }

    return false;
}

} // namespace process
