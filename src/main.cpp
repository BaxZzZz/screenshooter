#include <iostream>
#include <tclap/CmdLine.h>
#include <sys/stat.h>

#include "process/signal_handler.h"
#include "process/daemonizer.h"
#include "screen/jpeg_file_writer.h"
#include "screen/monitor.h"
#include "ui/display.h"

using screen::monitor;
using screen::jpeg_file_writer;

bool configure_options(int argc, char* argv[], bool& doDaemon, std::string& screenshot_path)
{
    try
    {
        TCLAP::CmdLine cmd("Application for catching screenshots of all active users' displays"
                           , ' ', "0.1");

        TCLAP::ValueArg<std::string> pathArg("p", "path", "Path for screenshots",
                                             false, "/tmp/screenshots", "string");
        cmd.add(pathArg);

        TCLAP::SwitchArg daemonArg("d","daemon","Daemonize process", cmd, false);

        cmd.parse(argc, argv);

        doDaemon        = daemonArg.getValue();
        screenshot_path = pathArg.getValue();
    }
    catch (TCLAP::ArgException& ex)
    {
        std::cout << "Error: " << ex.error() << std::endl;
        return false;
    }

    return true;
 }

int main(int argc, char* argv[])
{
    process::signal_register({ SIGINT, SIGTERM });

    bool doDaemon;
    std::string screenshot_path;

    if (!configure_options(argc, argv, doDaemon, screenshot_path))
    {
        return -1;
    }

    if (doDaemon)
    {
        if (!process::daemonize())
        {
            return -1;
        }
    }

    std::cout << "Start screenshooter application, path: " << screenshot_path << std::endl;

    mkdir(screenshot_path.c_str(), 0777);

    try
    {
        monitor screen_monitor;
        jpeg_file_writer::ptr_array writers;

        auto display_names = ui::find_active_displays();

        for (const auto& display_name : display_names)
        {
            auto writer = std::make_shared<jpeg_file_writer>(screenshot_path);
            screen_monitor.add_display(display_name, *writer);
            writers.push_back(std::move(writer));
        }

        process::wait_signals();
        screen_monitor.remove_all();
    }
    catch (std::exception& ex)
    {
        std::cout << ex.what() << std::endl;
        return -1;
    }

    std::cout << "Stop screenshooter application" << std::endl;

    return 0;
}
