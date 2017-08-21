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

    if (pid == 0)
    {
        umask(0);
        setsid();

        if (chdir("/") != 0)
        {
            return  false;
        }

        close(STDIN_FILENO);
        close(STDOUT_FILENO);
        close(STDERR_FILENO);

        return true;
    }

    return false;
}

} // namespace process
