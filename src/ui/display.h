#ifndef UI_DISPLAY_H
#define UI_DISPLAY_H

#include <memory>
#include <string>
#include <vector>
#include <X11/Xlib.h>

#include "ui/image.h"

namespace ui
{

/*!
 * \brief Class wrapper of XDisplay entity
 */
class display
{

public:

    /*!
     * \brief Array of display names
     */
    using names = std::vector<std::string>;

public:

    ~display();

    /*!
     * \brief Method for opening X11 display
     * \param [in] display_name - display name
     */
    void open(const std::string& display_name);

    /*!
     * \brief Method for closing X11 display
     */
    void close();

    /*!
     * \brief Method for getting display's images
     * \return Return image pointer
     */
    image::ptr get_image();

    /*!
     * \brief Mehtod for getting current display name
     * \return Return string of display name
     */
    const std::string& get_name() const;

private:

    Display*    x11_display_ = nullptr;
    std::string name_;

};

/*!
 * \brief Function for searching names of active displays
 * \return Return array of display names
 */
display::names find_active_displays();

} // namespace ui

#endif // UI_DISPLAY_H
