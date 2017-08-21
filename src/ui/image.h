#ifndef UI_IMAGE_H
#define UI_IMAGE_H

#include <memory>
#include <X11/Xlib.h>

namespace ui
{

/*!
 * \brief Class wrapper of XImage entity
 */
class image
{

public:

    using ptr = std::shared_ptr<image>;

public:

    /*!
     * \brief Constructor
     * \param [in] x11_image_ - pointer on XImage
     */
    image(XImage* x11_image_);

    ~image();

    /*!
     * \brief Method for getting pixel
     * \param [in] x - X coordinate
     * \param [in] y - Y coordinate
     * \return Return pixel value
     */
    std::size_t get_pixel(int x, int y) const;

    /*!
     * \brief Method for getting image width
     * \return Return width value
     */
    std::size_t get_width() const;

    /*!
     * \brief Method for getting image height
     * \return Return height value
     */
    std::size_t get_height() const;

    /*!
     * \brief Method for getting image depth
     * \return Return depth value
     */
    int get_depth() const;

private:

    XImage* x11_image_;

};

} // namespace ui

#endif // UI_IMAGE_H
