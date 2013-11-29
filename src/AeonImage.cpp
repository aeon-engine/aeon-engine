#include "Aeon.h"
#include "AeonImage.h"
#include "AeonConsole.h"

namespace Aeon
{

Image::Image()
:
Resource(Resource::Type::Image),
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
		Console::warning("Image::setData buffer empty.");
		return;
	}

	m_buffer = buffer;
	m_width = width;
	m_height = height;
	m_pixel_format = pixelformat;

	__set_loaded();
}

} //namespace Aeon
