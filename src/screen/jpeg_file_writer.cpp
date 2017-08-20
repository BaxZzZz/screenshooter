#include <sstream>
#include <iomanip>
#include <chrono>
#include <jpeglib.h>

#include "screen/jpeg_file_writer.h"

namespace screen
{

const std::string TIME_FORMAT = "%Y-%m-%d_%H:%M:%S";

namespace
{

std::string get_current_time_as_string()
{
    using namespace std::chrono;
    auto now      = system_clock::now();
    auto ms       = duration_cast<milliseconds>(now.time_since_epoch()) % 1000;
    auto datetime = system_clock::to_time_t(now);

    std::ostringstream oss;
    oss << std::put_time(std::localtime(&datetime), TIME_FORMAT.c_str());
    oss << '.' << std::setfill('0') << std::setw(3) << ms.count();

    return  oss.str();
}

} // namespace

jpeg_file_writer::jpeg_file_writer(const std::string& path) :
    path_(path)
{

}

void jpeg_file_writer::write(const std::string& filename, const ui::image::ptr image)
{
    if (filename.empty())
    {
        throw std::runtime_error("empty filename");
    }

    auto file = std::fopen(filename.c_str(), "wb");

    if (file == nullptr)
    {
        throw std::runtime_error("Failed to open output file: " + filename);
    }

    std::vector<std::uint8_t> buffer(3 * image->get_width() * image->get_height());

    for (std::size_t y = 0; y < image->get_height(); ++y)
    {
        for (std::size_t x = 0; x < image->get_width(); ++x)
        {
            auto pixel = image->get_pixel(int(x), int(y));
            buffer[y * image->get_width() * 3 + x * 3 + 0] = std::uint8_t(pixel >> 16);
            buffer[y * image->get_width() * 3 + x * 3 + 1] = std::uint8_t((pixel & 0x00ff00) >> 8);
            buffer[y * image->get_width() * 3 + x * 3 + 2] = std::uint8_t(pixel & 0x0000ff);
        }
    }

    jpeg_compress_struct cinfo;
    jpeg_error_mgr       jerr;

    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_compress(&cinfo);
    jpeg_stdio_dest(&cinfo, file);

    cinfo.image_width      = image->get_width();
    cinfo.image_height     = image->get_height();
    cinfo.input_components = 3;
    cinfo.in_color_space   = JCS_RGB;

    jpeg_set_defaults(&cinfo);
    jpeg_set_quality(&cinfo, 85, TRUE);
    jpeg_start_compress(&cinfo, TRUE);

    while (cinfo.next_scanline < cinfo.image_height)
    {
        auto index       = cinfo.next_scanline * (image->get_depth() >> 3) * image->get_width();
        auto row_pointer = static_cast<JSAMPROW>(&buffer[index]);
        jpeg_write_scanlines(&cinfo, &row_pointer, 1);
    }

    jpeg_finish_compress(&cinfo);
    fclose(file);
}

void jpeg_file_writer::on_image_received(const std::string& display_name,
                                         const ui::image::ptr image)
{
    auto filename = path_+ '/' + display_name + '-' + get_current_time_as_string() + ".jpeg";
    write(filename, image);
}

} // namespace screen
