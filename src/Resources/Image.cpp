#include "Aeon.h"
#include "AeonImage.h"
#include "AeonConsole.h"

namespace Aeon
{

Image::Image()
:
m_width(0),
m_height(0),
m_pixel_format(PixelFormat::RGBA)
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

	m_buffer = buffer;
	m_width = width;
	m_height = height;
	m_pixel_format = pixelformat;
}

bool Image::save_raw_to_stream(StreamPtr stream)
{
	if(!stream)
		return false;

	if(!stream->good())
		return false;

	if(!m_buffer)
		return false;

	if(m_buffer->get() == NULL)
		return false;

	if(stream->write(m_buffer->get(), m_buffer->size()) != m_buffer->size())
		return false;

	return true;
}

} //namespace Aeon
