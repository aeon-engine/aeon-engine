#ifndef AeonImageCodecPNG_h__
#define AeonImageCodecPNG_h__

#include "AeonImageCodec.h"

namespace Aeon
{

class ImageCodecPNG : public ImageCodec
{
public:
	ImageCodecPNG();
	virtual ~ImageCodecPNG();

	virtual ImagePtr decode(StreamPtr stream);
	virtual std::string get_type_name() const;
};

} //namespace Aeon

#endif // AeonImageCodecPNG_h__
