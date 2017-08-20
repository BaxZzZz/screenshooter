#ifndef UI_IMAGE_H
#define UI_IMAGE_H

#include <memory>
#include <X11/Xlib.h>

namespace ui
{

class image
{

public:

    using ptr = std::shared_ptr<image>;

public:

    image(XImage* x11_image_);

    ~image();

    std::size_t get_pixel(int x, int y) const;

    std::size_t get_width() const;

    std::size_t get_height() const;

    int get_depth() const;

private:

    XImage* x11_image_;

};

} // namespace ui

#endif // UI_IMAGE_H
