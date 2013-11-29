#ifndef ImageLoader_h__
#define ImageLoader_h__

namespace Aeon
{

class ImageLoader
{
public:
	ImageLoader(){}
	virtual ~ImageLoader() {}

	virtual bool		load(ImagePtr image, const char *path) = 0;
	virtual bool		load(ImagePtr image, BufferPtr buffer) = 0;
};

typedef std::shared_ptr<ImageLoader>		ImageLoaderPtr;

} //namespace Aeon

#endif // ImageLoader_h__
