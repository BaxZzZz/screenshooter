#ifndef SCREEN_MONITOR_H
#define SCREEN_MONITOR_H

#include <unordered_map>

#include "screen/shooter.h"
#include "screen/image_event_handler.h"

namespace screen
{

class monitor
{

public:

    ~monitor();

    void add_display(const std::string& display_name, image_event_handler& event_handler);

    void remove_display(const std::string& display_name);

    void remove_all();

private:

    using shooter_table = std::unordered_map<std::string, shooter::ptr>;

private:

    shooter_table shooters_;

};

} // namespace screen

#endif // SCREEN_MONITOR_H
