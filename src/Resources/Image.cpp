#include "Aeon/Aeon.h"
#include "Aeon/Resources/Image.h"
#include "Aeon/Console/Console.h"

namespace Aeon
{

Image::Image()
:
width_(0),
height_(0),
pixel_format_(PixelFormat::RGBA)
{

}

Image::~Image()
{

}

void Image::set_data(BufferPtr buffer, unsigned int width, unsigned int height, PixelFormat pixelformat /*= PixelFormat::RGBA*/)
{
	if (buffer == NULL || buffer->get() == NULL)
	{
		Console::error("Image: Tried creating an image from an empty buffer.");
		return;
	}

	buffer_ = buffer;
	width_ = width;
	height_ = height;
	pixel_format_ = pixelformat;
}

bool Image::save_raw_to_stream(StreamPtr stream)
{
	if(!stream)
		return false;

	if(!stream->good())
		return false;

	if(!buffer_)
		return false;

	if(buffer_->get() == NULL)
		return false;

	if(stream->write(buffer_->get(), buffer_->size()) != buffer_->size())
		return false;

	return true;
}

} //namespace Aeon
