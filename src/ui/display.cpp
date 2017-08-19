#include <cassert>
#include <dirent.h>
#include <cstring>
#include <X11/Xatom.h>
#include <X11/Xutil.h>

#include "ui/display.h"

namespace ui
{

const std::string X11_UNIX_DIR = "/tmp/.X11-unix";

display::~display()
{
    if (x11_display_ != nullptr)
    {
        close();
    }
}

void display::open(const std::string& display_name)
{
    if (x11_display_ != nullptr)
    {
        throw std::runtime_error("X11 display already opened");
    }

    x11_display_ = XOpenDisplay(display_name.c_str());

    if (x11_display_ == nullptr)
    {
        throw std::runtime_error("Сan't open X11 display with name " + display_name);
    }

    name_ = display_name;
}

void display::close()
{
    if (x11_display_ == nullptr)
    {
        throw std::runtime_error("X11 display already closed");
    }

    XCloseDisplay(x11_display_);
    x11_display_ = nullptr;
    name_.clear();
}

image::ptr display::get_image()
{
    auto root = XDefaultRootWindow(x11_display_);

    XWindowAttributes attributes{};

    if (XGetWindowAttributes(x11_display_, root, &attributes) != True)
    {
        throw std::runtime_error("Can't get X11 window attributes from display: " + name_);
    }

    auto x11_image = XGetImage(x11_display_,
                               root,
                               0,
                               0,
                               attributes.width,
                               attributes.height,
                               AllPlanes,
                               ZPixmap);

    if (x11_image == nullptr)
    {
        throw std::runtime_error("Can't get X11 image from display: " + name_);
    }

    return std::make_shared<image>(x11_image);
}

const std::string& display::get_name() const
{
    return name_;
}

display::names find_active_displays()
{
    display::names display_names;

    auto directory = opendir(X11_UNIX_DIR.c_str());

    if (directory == nullptr)
    {
        throw std::runtime_error("Can't open directory: " + X11_UNIX_DIR);
    }

    dirent* entry;

    while ((entry = readdir(directory)) != NULL)
    {
        if (entry->d_name[0] != 'X')
        {
            continue;
        }

        std::string display_name(":");
        display_name += entry->d_name + 1;
        display_names.push_back(std::move(display_name));
    }

    closedir(directory);

    return display_names;
}

} // namespace ui
