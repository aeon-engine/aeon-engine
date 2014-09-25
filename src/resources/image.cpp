#include "aeon/aeon.h"
#include "aeon/resources/image.h"
#include "aeon/console/console.h"

namespace aeon
{

image::image()
:
width_(0),
height_(0),
pixel_format_(pixel_format::rgba)
{

}

image::~image()
{

}

void image::set_data(buffer_ptr buffer, unsigned int width, 
	unsigned int height, pixel_format pixelformat /*= pixel_format::rgba*/)
{
	if(buffer == NULL || buffer->get() == NULL)
	{
		console::error("[Image]: Tried creating an image from an "
			"empty buffer.");
		return;
	}

	buffer_ = buffer;
	width_ = width;
	height_ = height;
	pixel_format_ = pixelformat;
}

bool image::save_raw_to_stream(stream_ptr stream)
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

} //namespace aeon
