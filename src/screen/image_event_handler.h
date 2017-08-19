#ifndef SCREEN_IMAGE_EVENT_HANDLER_H
#define SCREEN_IMAGE_EVENT_HANDLER_H

#include <string>

#include "ui/image.h"

namespace screen
{

class image_event_handler
{

public:

    virtual ~image_event_handler() = default;

    virtual void on_image_received(const std::string& display_name,
                                   const ui::image::ptr image) = 0;

};

} // namespace screen

#endif // SCREEN_IMAGE_EVENT_HANDLER_H
