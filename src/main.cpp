#include <iostream>
#include <fstream>
#include <atomic>
#include <csignal>

#include "ui/display.h"
#include "screen/image_file_writer.h"
#include "screen/monitor.h"

namespace
{

std::atomic<bool> is_running { true };

void signal_handler(int signal_number)
{
    std::cout << "Interrupt signal " << signal_number << " received." << std::endl;
    is_running = false;
}

} // namespace

const std::string DEFAULT_PATH = "/tmp";

using screen::monitor;
using screen::image_file_writer;

int main()
{
    signal(SIGINT, signal_handler);

    try
    {
        monitor screen_monitor;
        image_file_writer::ptr_array writers;

        auto display_names = ui::find_active_displays();

        for (const auto& display_name : display_names)
        {
            auto writer = std::make_shared<image_file_writer>(DEFAULT_PATH);
            screen_monitor.add_display(display_name, *writer);
            writers.push_back(std::move(writer));
        }

        std::cout << "Application started." << std::endl;

        while (is_running)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }

        screen_monitor.remove_all();

        std::cout << "Application stoppped." << std::endl;
    }
    catch (std::exception& ex)
    {
        std::cout << ex.what() << std::endl;
        return -1;
    }

    return 0;
}
