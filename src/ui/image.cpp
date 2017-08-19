#include <X11/Xutil.h>

#include "ui/image.h"

namespace ui
{

image::image(XImage* image) : x11_image_(image)
{

}

image::~image()
{
    if (x11_image_ != nullptr)
    {
        XDestroyImage(x11_image_);
        x11_image_ = nullptr;
    }
}

std::size_t image::get_pixel(int x, int y) const
{
    return XGetPixel(x11_image_,x,y);
}

int image::get_width() const
{
    return x11_image_->width;
}

int image::get_height() const
{
    return x11_image_->height;
}

int image::get_depth() const
{
    return x11_image_->depth;
}

} // namespace ui
