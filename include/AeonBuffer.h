#ifndef AeonBuffer_h__
#define AeonBuffer_h__

namespace Aeon
{

class Buffer
{
public:
	Buffer();
	Buffer(long size);
	~Buffer();

	void				alloc(long size);
	void				free();

	unsigned char *		get()		{ return m_buffer; }
	long				size()		{ return m_size; }

private:
	unsigned char *		m_buffer;
	long				m_size;
};

typedef std::shared_ptr<Buffer> BufferPtr;

} //namespace Aeon

#endif // AeonBuffer_h__
