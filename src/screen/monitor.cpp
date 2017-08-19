#include "screen/monitor.h"

namespace screen
{

monitor::~monitor()
{
    if (!shooters_.empty())
    {
        remove_all();
    }
}

void monitor::add_display(const std::string& display_name, image_event_handler& event_handler)
{
    if (display_name.empty())
    {
        throw std::runtime_error("Empty display name");
    }

    if (shooters_.find(display_name) != shooters_.end())
    {
        throw std::runtime_error("Display name: " +  display_name + " already exists");
    }

    auto screen_shooter = std::make_shared<shooter>();
    screen_shooter->start(display_name, event_handler);
    shooters_[display_name] = std::move(screen_shooter);
}

void monitor::remove_display(const std::string& display_name)
{
    auto shooter_info_it = shooters_.find(display_name);

    if (shooter_info_it == shooters_.end())
    {
        throw std::runtime_error("Can't find display_name: " + display_name);
    }

    auto& screen_shooter = shooter_info_it->second;
    screen_shooter->stop();
    shooters_.erase(shooter_info_it);
}

void monitor::remove_all()
{
    for (auto& shooter_info_it : shooters_)
    {
        shooter_info_it.second->stop();
    }

    shooters_.clear();
}

} // namespace screen
