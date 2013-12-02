#include "Aeon.h"
#include "AeonFileInput.h"
#include "AeonImage.h"
#include "AeonImageLoader.h"
#include "AeonImageLoader_png.h"
#include "AeonConsole.h"
#include <png.h>

namespace Aeon
{
#if 0
ImageLoaderPng::ImageLoaderPng()
{

}

ImageLoaderPng::~ImageLoaderPng()
{

}

bool ImageLoaderPng::load(ImagePtr image, const char *path)
{
	//Open the new file
	File::Input file;

	if(!file.open(path))
		return false;

	size_t filesize = file.size();

	if(filesize == 0)
	{
		Console::error("Could not load PNG %s. File empty.", path);
		return false;
	}

	//Read the header
	png_byte png_header[8];
	file.read(png_header, 8);
	
	//Check the header
	if (png_sig_cmp(png_header, 0, 8))
    {
		Console::error("Could not load PNG %s. Not a valid PNG file.", path);
        return false;
    }

	//Create the read struct for PNG
	png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png_ptr)
    {
		Console::error("png_create_read_struct returned 0.");
        return false;
    }

	// create png info struct
    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr)
    {
		Console::error("png_create_info_struct returned 0.");
        png_destroy_read_struct(&png_ptr, (png_infopp)NULL, (png_infopp)NULL);
        return false;
    }

	//create png info struct
    png_infop end_info = png_create_info_struct(png_ptr);
    if (!end_info)
    {
        Console::error("png_create_info_struct returned 0.");
        png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp) NULL);
        return false;
    }

	//Bind errors from libpng
	if (setjmp(png_jmpbuf(png_ptr)))
	{
		Console::error("libPNG reported an error.");
        png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
        return false;
    }

	// init png reading
    png_init_io(png_ptr, file.get_descriptor());

    // let libpng know you already read the first 8 bytes
    png_set_sig_bytes(png_ptr, 8);

    // read all the info up to the image data
    png_read_info(png_ptr, info_ptr);

    // variables to pass to get info
    int bit_depth, color_type;
    png_uint_32 temp_width, temp_height;

    // get info about png
    png_get_IHDR(png_ptr, info_ptr, &temp_width, &temp_height, &bit_depth, &color_type, NULL, NULL, NULL);

	//Check the pixel format
	Image::PixelFormat pixelformat = Image::PixelFormat::RGB;
	if(color_type == PNG_COLOR_TYPE_RGB)
	{
		pixelformat = Image::PixelFormat::RGB;
		Console::debug("RGB Pixel format is RGB");
	}
	else if(color_type == PNG_COLOR_TYPE_RGB_ALPHA)
	{
		pixelformat = Image::PixelFormat::RGBA;
		Console::debug("RGB Pixel format is RGBA");
	}else{
		Console::error("Unsupported PNG pixel format.");
		png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
		return false;
	}

    // Update the png info struct.
	png_read_update_info(png_ptr, info_ptr);

	int rowbytes = png_get_rowbytes(png_ptr, info_ptr);

    // glTexImage2d requires rows to be 4-byte aligned
    //rowbytes += 3 - ((rowbytes-1) % 4);

    // Allocate the image_data as a big block, to be given to opengl
	BufferPtr bitmapBuffer = BufferPtr(new Buffer(rowbytes * temp_height * sizeof(png_byte)/* + 15*/));
	
	if (bitmapBuffer == NULL || bitmapBuffer->get() == NULL)
	{
		Console::error("Could not allocate memory for PNG image data.");
		png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
		return false;
	}
	
	//Cast to png_byte since this is what libpng likes as buffer. Just passing the pointer
	//should be fine. But this ensures 100% compatibility.
	png_byte * image_data = (png_byte *) bitmapBuffer->get();

	// row_pointers is for pointing to image_data for reading the png with libpng

	BufferPtr rowPointerBuffer = BufferPtr(new Buffer(temp_height * sizeof(png_bytep)));

	if (rowPointerBuffer == NULL || rowPointerBuffer->get() == NULL)
	{
		Console::error("Could not allocate memory for PNG row pointers.");
		png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
		return false;
	}

	//cast to png_bytep
	png_bytep * row_pointers = (png_bytep *) rowPointerBuffer->get();

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
	image->set_data(bitmapBuffer, temp_width, temp_height, pixelformat);

	return true;
}

bool ImageLoaderPng::load(ImagePtr image, BufferPtr buffer)
{
	//TODO: Implement loading PNG from memory.
	return false;
}
#endif
} //namespace Aeon
