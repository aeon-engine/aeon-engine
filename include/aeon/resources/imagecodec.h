#ifndef AeonImageCodec_h__
#define AeonImageCodec_h__

#include "Aeon/Streams/Stream.h"
#include "Aeon/Resources/Image.h"

namespace Aeon
{

class ImageCodec
{
public:
	ImageCodec() {}
	virtual ~ImageCodec() {}

	virtual ImagePtr decode(StreamPtr stream) = 0;
	virtual std::string get_type_name() const = 0;

};

typedef std::shared_ptr<ImageCodec> ImageCodecPtr;

} /* namespace Aeon */

#endif /* AeonImageCodec_h__ */
