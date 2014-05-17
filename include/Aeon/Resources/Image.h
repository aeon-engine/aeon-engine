#ifndef AeonImage_h__
#define AeonImage_h__

#include "Aeon/Utility/Buffer.h"
#include "Aeon/Streams/Stream.h"

namespace Aeon
{

class Image
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

	BufferPtr				get_data()			{ return buffer_; }
	unsigned int			get_width()			{ return width_; }
	unsigned int			get_height()		{ return height_; }
	PixelFormat				get_pixelformat()	{ return pixel_format_; }

	bool					save_raw_to_stream(StreamPtr stream);

private:
	BufferPtr				buffer_;

	unsigned int			width_;
	unsigned int			height_;
	PixelFormat				pixel_format_;
};

typedef std::shared_ptr<Image> ImagePtr;
#define AeonEmptyImage ImagePtr();

} //namespace Aeon

#endif /* AeonImage_h__ */
