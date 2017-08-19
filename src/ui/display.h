#ifndef UI_DISPLAY_H
#define UI_DISPLAY_H

#include <memory>
#include <string>
#include <vector>
#include <X11/Xlib.h>

#include "ui/image.h"

namespace ui
{

class display
{

public:

    using names = std::vector<std::string>;

public:

    ~display();

    void open(const std::string& display_name);

    void close();

    image::ptr get_image();

    const std::string& get_name() const;

private:

    Display*    x11_display_ = nullptr;
    std::string name_;

};

display::names find_active_displays();

} // namespace ui

#endif // UI_DISPLAY_H
