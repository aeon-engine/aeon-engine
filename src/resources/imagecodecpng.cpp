#include "aeon/stdafx.h"

#ifdef AEON_USE_PNG

#include "aeon/resources/imagecodecpng.h"
#include "aeon/console/console.h"
#include <png.h>

#define PNG_HEADER_SIGNATURE_SIZE 8

namespace aeon
{

static void __png_read_callback(png_structp png_ptr, png_bytep output_ptr, 
    png_size_t output_size)
{
    stream_ptr *stream = (stream_ptr *)png_get_io_ptr(png_ptr);

    // Do we have a stream?
    if(!stream)
    {
        console::error("[ImageCodec]: Could not decode PNG. Stream was null "
            "in read callback.");
        return;
    }

    // Read the data
    if((*stream)->read(output_ptr, (size_t) output_size) != output_size)
    {
        console::error("[ImageCodec]: Could not decode PNG. Unexpected end "
            "of stream in read callback.");
        return;
    }
}

image_codec_png::image_codec_png()
{

}

image_codec_png::~image_codec_png()
{

}

image_ptr image_codec_png::decode(stream_ptr stream)
{
    // Check our stream
    if (!stream)
    {
        console::error("[ImageCodec]: Could not decode PNG '%s'. "
            "Stream was null.", stream->get_name().c_str());
        return aeon_empty_image;
    }

    if(!stream->good())
    {
        console::error("[ImageCodec]: Could not decode PNG '%s'. "
            "Stream was bad.", stream->get_name().c_str());
        return aeon_empty_image;
    }

    size_t size = stream->size();

    if (size == 0)
    {
        console::error("[ImageCodec]: Could not decode PNG '%s'. "
            "Stream was empty.", stream->get_name().c_str());
        return aeon_empty_image;
    }

    // Read the header
    png_byte png_header[PNG_HEADER_SIGNATURE_SIZE];
    stream->read(png_header, PNG_HEADER_SIGNATURE_SIZE);

    // Check the header
    if (png_sig_cmp(png_header, 0, PNG_HEADER_SIGNATURE_SIZE))
    {
        console::error("[ImageCodec]: Could not decode PNG '%s'. "
            "Not a valid PNG format.", stream->get_name().c_str());
        return aeon_empty_image;
    }

    // Create the read struct for PNG
    png_structp png_ptr = png_create_read_struct(
        PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png_ptr)
    {
        console::error("[ImageCodec]: Could not decode PNG '%s'. "
            "png_create_read_struct failed.", stream->get_name().c_str());
        return aeon_empty_image;
    }

    // Create png info struct
    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr)
    {
        console::error("[ImageCodec]: Could not decode PNG '%s'. "
            "png_create_info_struct failed.", stream->get_name().c_str());
        png_destroy_read_struct(&png_ptr, (png_infopp)NULL, (png_infopp)NULL);
        return aeon_empty_image;
    }

    // Create png info struct
    png_infop end_info = png_create_info_struct(png_ptr);
    if (!end_info)
    {
        console::error("[ImageCodec]: Could not decode PNG '%s'. "
            "png_create_info_struct failed.", stream->get_name().c_str());
        png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp)NULL);
        return aeon_empty_image;
    }

    // Bind errors from libpng
    if (setjmp(png_jmpbuf(png_ptr)))
    {
        console::error("[ImageCodec]: Could not decode PNG '%s'. "
            "libPNG reported an error.", stream->get_name().c_str());
        png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
        return aeon_empty_image;
    }

    // Init png reading. We will be using a read function, as we can't read 
    // from a file.
    png_set_read_fn(png_ptr, &stream, __png_read_callback);

    // Let libpng know we already read the signature
    png_set_sig_bytes(png_ptr, PNG_HEADER_SIGNATURE_SIZE);

    // Read all the info up to the image data
    png_read_info(png_ptr, info_ptr);

    // Variables to pass to get info
    int bit_depth, color_type;
    png_uint_32 temp_width, temp_height;

    // Get info about png
    png_get_IHDR(png_ptr, info_ptr, &temp_width, &temp_height, &bit_depth, 
        &color_type, NULL, NULL, NULL);

    // Check the pixel format
    image::pixel_format pixelformat = image::pixel_format::rgb;
    if (color_type == PNG_COLOR_TYPE_RGB)
    {
        pixelformat = image::pixel_format::rgb;
        console::debug("[ImageCodec]: RGB Pixel format is RGB");
    }
    else if (color_type == PNG_COLOR_TYPE_RGB_ALPHA)
    {
        pixelformat = image::pixel_format::rgba;
        console::debug("[ImageCodec]: RGB Pixel format is RGBA");
    }
    else
    {
        console::error("[ImageCodec]: Could not decode PNG '%s'. "
            "Unsupported PNG pixel format.", stream->get_name().c_str());
        png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
        return aeon_empty_image;
    }

    // Update the png info struct.
    png_read_update_info(png_ptr, info_ptr);

    size_t rowbytes = png_get_rowbytes(png_ptr, info_ptr);

    // Allocate the image_data as a big block
    size_t bitmap_buff_size = rowbytes * 
        size_t(temp_height) * sizeof(png_byte);
    auto bitmap_buffer = std::make_shared<buffer>(bitmap_buff_size);

    if (bitmap_buffer == NULL || bitmap_buffer->get() == NULL)
    {
        console::error("[ImageCodec]: Could not allocate memory for "
            "PNG image data.");
        png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
        return aeon_empty_image;
    }

    // Cast to png_byte since this is what libpng likes as buffer. 
    // Just passing the pointer should be fine. But this ensures 100% 
    // compatibility.
    png_byte * image_data = (png_byte *)bitmap_buffer->get();

    // Row_pointers is for pointing to image_data for reading the 
    // png with libpng
    size_t rowpointer_buff_size = size_t(temp_height) * sizeof(png_bytep);
    auto rowpointer_buffer = std::make_shared<buffer>(rowpointer_buff_size);

    if (rowpointer_buffer == NULL || rowpointer_buffer->get() == NULL)
    {
        console::error("[ImageCodec]: Could not decode PNG '%s'. "
            "Could not allocate memory for PNG row pointers.", 
            stream->get_name().c_str());
        png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
        return aeon_empty_image;
    }

    // Cast to png_bytep
    png_bytep * row_pointers = (png_bytep *) rowpointer_buffer->get();

    // Set the individual row_pointers to point at the correct offsets 
    // of image_data
    for (size_t i = 0; i < size_t(temp_height); i++)
    {
        row_pointers[i] = image_data + i * rowbytes;
    }

    // Read the png into image_data through row_pointers
    png_read_image(png_ptr, row_pointers);

    // Cleanup
    png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);

    //Load the data into the image object
    auto img = std::make_shared<image>();
    bitmap_buffer->set_size(bitmap_buffer->reserved_size());
    img->set_data(bitmap_buffer, temp_width, temp_height, pixelformat);
    return img;
}

std::string image_codec_png::get_type_name() const
{
    return "PNG";
}

} /* namespace aeon */

#endif /* AEON_USE_PNG */
