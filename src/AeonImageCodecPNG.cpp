#include "Aeon.h"
#include "AeonImageCodecPNG.h"
#include "AeonConsole.h"
#include <png.h>

#define PNG_HEADER_SIGNATURE_SIZE 8

namespace Aeon
{

static void __png_read_callback(png_structp png_ptr, png_bytep output_ptr, png_size_t output_size)
{
	StreamPtr *stream = (StreamPtr *)png_get_io_ptr(png_ptr);

	//Do we have a stream?
	if(!stream)
	{
		Console::error("ImageCodecPNG: Could not decode PNG. Stream was null in read callback.");
		return;
	}

	//Read the data
	if ((*stream)->read(output_ptr, (size_t) output_size) != output_size)
	{
		Console::error("ImageCodecPNG: Could not decode PNG. Unexpected end of stream in read callback.");
		return;
	}
}

ImageCodecPNG::ImageCodecPNG()
{

}

ImageCodecPNG::~ImageCodecPNG()
{

}

ImagePtr ImageCodecPNG::decode(StreamPtr stream)
{
	//Check our stream
	if (!stream)
	{
		Console::error("ImageCodecPNG: Could not decode PNG '%s'. Stream was null.", stream->get_name().c_str());
		return AeonEmptyImage;
	}

	if(!stream->good())
	{
		Console::error("ImageCodecPNG: Could not decode PNG '%s'. Stream was bad.", stream->get_name().c_str());
		return AeonEmptyImage;
	}

	size_t size = stream->size();

	if (size == 0)
	{
		Console::error("ImageCodecPNG: Could not decode PNG '%s'. Stream was empty.", stream->get_name().c_str());
		return AeonEmptyImage;
	}

	//Read the header
	png_byte png_header[PNG_HEADER_SIGNATURE_SIZE];
	stream->read(png_header, PNG_HEADER_SIGNATURE_SIZE);

	//Check the header
	if (png_sig_cmp(png_header, 0, PNG_HEADER_SIGNATURE_SIZE))
	{
		Console::error("ImageCodecPNG: Could not decode PNG '%s'. Not a valid PNG format.", stream->get_name().c_str());
		return AeonEmptyImage;
	}

	//Create the read struct for PNG
	png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (!png_ptr)
	{
		Console::error("ImageCodecPNG: Could not decode PNG '%s'. png_create_read_struct failed.", stream->get_name().c_str());
		return AeonEmptyImage;
	}

	// create png info struct
	png_infop info_ptr = png_create_info_struct(png_ptr);
	if (!info_ptr)
	{
		Console::error("ImageCodecPNG: Could not decode PNG '%s'. png_create_info_struct failed.", stream->get_name().c_str());
		png_destroy_read_struct(&png_ptr, (png_infopp)NULL, (png_infopp)NULL);
		return AeonEmptyImage;
	}

	//create png info struct
	png_infop end_info = png_create_info_struct(png_ptr);
	if (!end_info)
	{
		Console::error("ImageCodecPNG: Could not decode PNG '%s'. png_create_info_struct failed.", stream->get_name().c_str());
		png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp)NULL);
		return AeonEmptyImage;
	}

	//Bind errors from libpng
	if (setjmp(png_jmpbuf(png_ptr)))
	{
		Console::error("ImageCodecPNG: Could not decode PNG '%s'. libPNG reported an error.", stream->get_name().c_str());
		png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
		return AeonEmptyImage;
	}

	// init png reading. We will be using a read function, as we can't read from a file.
	png_set_read_fn(png_ptr, &stream, __png_read_callback); //png_init_io(png_ptr, file.get_descriptor());

	// let libpng know we already read the signature
	png_set_sig_bytes(png_ptr, PNG_HEADER_SIGNATURE_SIZE);

	// read all the info up to the image data
	png_read_info(png_ptr, info_ptr);

	// variables to pass to get info
	int bit_depth, color_type;
	png_uint_32 temp_width, temp_height;

	// get info about png
	png_get_IHDR(png_ptr, info_ptr, &temp_width, &temp_height, &bit_depth, &color_type, NULL, NULL, NULL);

	//Check the pixel format
	Image::PixelFormat pixelformat = Image::PixelFormat::RGB;
	if (color_type == PNG_COLOR_TYPE_RGB)
	{
		pixelformat = Image::PixelFormat::RGB;
		Console::debug("ImageCodecPNG: RGB Pixel format is RGB");
	}
	else if (color_type == PNG_COLOR_TYPE_RGB_ALPHA)
	{
		pixelformat = Image::PixelFormat::RGBA;
		Console::debug("ImageCodecPNG: RGB Pixel format is RGBA");
	}
	else{
		Console::error("ImageCodecPNG: Could not decode PNG '%s'. Unsupported PNG pixel format.", stream->get_name().c_str());
		png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
		return AeonEmptyImage;
	}

	// Update the png info struct.
	png_read_update_info(png_ptr, info_ptr);

	int rowbytes = png_get_rowbytes(png_ptr, info_ptr);

	// glTexImage2d requires rows to be 4-byte aligned
	//rowbytes += 3 - ((rowbytes-1) % 4);

	// Allocate the image_data as a big block
	auto bitmapBuffer = std::make_shared<Buffer>(rowbytes * temp_height * sizeof(png_byte)/* + 15*/);

	if (bitmapBuffer == NULL || bitmapBuffer->get() == NULL)
	{
		Console::error("Could not allocate memory for PNG image data.");
		png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
		return AeonEmptyImage;
	}

	//Cast to png_byte since this is what libpng likes as buffer. Just passing the pointer
	//should be fine. But this ensures 100% compatibility.
	png_byte * image_data = (png_byte *)bitmapBuffer->get();

	// row_pointers is for pointing to image_data for reading the png with libpng

	auto rowPointerBuffer = std::make_shared<Buffer>(temp_height * sizeof(png_bytep));

	if (rowPointerBuffer == NULL || rowPointerBuffer->get() == NULL)
	{
		Console::error("ImageCodecPNG: Could not decode PNG '%s'. Could not allocate memory for PNG row pointers.", stream->get_name().c_str());
		png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
		return AeonEmptyImage;
	}

	//cast to png_bytep
	png_bytep * row_pointers = (png_bytep *)rowPointerBuffer->get();

	// set the individual row_pointers to point at the correct offsets of image_data
	for (unsigned int i = 0; i < temp_height; i++)
	{
		row_pointers[i] = image_data + i * rowbytes;
	}

	// read the png into image_data through row_pointers
	png_read_image(png_ptr, row_pointers);

	// Cleanup
	png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);

	//Load the data into the image object
	auto image = std::make_shared<Image>();
	bitmapBuffer->set_size(bitmapBuffer->reserved_size());
	image->set_data(bitmapBuffer, temp_width, temp_height, pixelformat);
	return image;
}

std::string ImageCodecPNG::get_type_name() const
{
	return "PNG";
}

} //namespace Aeon
