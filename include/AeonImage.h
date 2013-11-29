#ifndef AeonImage_h__
#define AeonImage_h__

#include "AeonResource.h"
#include "AeonBuffer.h"

namespace Aeon
{

class Image : public Resource
{
public:
	enum class PixelFormat
	{
		RGB,
		RGBA,
	};

	Image();
	~Image();

	void					set_data(BufferPtr buffer, unsigned int width, unsigned int height, PixelFormat pixelformat = PixelFormat::RGBA);

	BufferPtr				get_data()			{ return m_buffer; }
	unsigned int			get_width()			{ return m_width; }
	unsigned int			get_height()		{ return m_height; }
	PixelFormat				get_pixelformat()	{ return m_pixel_format; }

private:
	BufferPtr				m_buffer;

	unsigned int			m_width;
	unsigned int			m_height;
	PixelFormat				m_pixel_format;
};

typedef std::shared_ptr<Image>	ImagePtr;
#define EMPTY_IMAGE		 ImagePtr();

} //namespace Aeon

#endif // AeonImage_h__
