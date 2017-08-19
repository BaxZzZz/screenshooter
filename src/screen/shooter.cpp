#include "screen/shooter.h"

namespace screen
{

shooter::~shooter()
{
    if (is_started_)
    {
        stop();
    }
}

void shooter::start(const std::string& display_name, image_event_handler& event_handler)
{
    if (is_started_)
    {
        throw std::runtime_error("shooter already started");
    }

    if (display_name.empty())
    {
        throw std::runtime_error("empty display name");
    }

    display_.open(display_name);

    even_handler_ = &event_handler;
    is_started_   = true;
    worker_       = std::thread(&shooter::run, this);
}

void shooter::stop()
{
    if (!is_started_)
    {
        throw std::runtime_error("shooter already stopped");
    }

    is_started_ = false;
    worker_.join();
    display_.close();
    even_handler_ = nullptr;
}

void shooter::run()
{
    while (is_started_)
    {
        even_handler_->on_image_received(display_.get_name(), display_.get_image());
    }
}

} // namespace screen
