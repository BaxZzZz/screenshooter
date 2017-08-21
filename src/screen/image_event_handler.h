#ifndef SCREEN_IMAGE_EVENT_HANDLER_H
#define SCREEN_IMAGE_EVENT_HANDLER_H

#include <string>

#include "ui/image.h"

namespace screen
{

/*!
 * \brief Interface of received image events handler
 */
class image_event_handler
{

public:

    virtual ~image_event_handler() = default;

    /*!
     * \brief Method of image reception event handling
     * \param [in] display_name - display name
     * \param [in] image        - image pointer
     */
    virtual void on_image_received(const std::string& display_name,
                                   const ui::image::ptr image) = 0;

};

} // namespace screen

#endif // SCREEN_IMAGE_EVENT_HANDLER_H
