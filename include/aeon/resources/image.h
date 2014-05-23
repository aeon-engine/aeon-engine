#ifndef image_h__
#define image_h__

#include "aeon/utility/buffer.h"
#include "aeon/streams/stream.h"

namespace aeon
{

class image
{
public:
	enum class pixel_format
	{
		rgb,
		rgba,
	};

	image();
	~image();

	void					set_data(buffer_ptr buffer, unsigned int width, unsigned int height, pixel_format pixelformat = pixel_format::rgba);

	buffer_ptr				get_data()			{ return buffer_; }
	unsigned int			get_width()			{ return width_; }
	unsigned int			get_height()		{ return height_; }
	pixel_format			get_pixelformat()	{ return pixel_format_; }

	bool					save_raw_to_stream(stream_ptr stream);

private:
	buffer_ptr				buffer_;

	unsigned int			width_;
	unsigned int			height_;
	pixel_format			pixel_format_;
};

typedef std::shared_ptr<image> image_ptr;
#define aeon_empty_image image_ptr();

} //namespace aeon

#endif // image_h__
