#ifndef AeonBuffer_h__
#define AeonBuffer_h__

namespace Aeon
{

class Buffer
{
public:
	enum class DeleteMode
	{
		None,
		DeleteOnDestruct
	};

	Buffer();
	Buffer(size_t size, DeleteMode delete_mode = DeleteMode::DeleteOnDestruct);
	Buffer(void *buffer, size_t size, DeleteMode delete_mode = DeleteMode::DeleteOnDestruct);
	~Buffer();

	//Prevent copying
	Buffer(const Buffer&) = delete;
	Buffer & operator=(const Buffer&) = delete;

	//Allocate at least n bytes
	bool				reserve(size_t n);

	//Resize to the specified size.
	bool				resize(size_t n);

	bool				append(void *data, size_t len);

	void				free();

	void *				get() { return m_buffer; }

	size_t				size() { return m_size; }
	size_t				reserved_size() { return m_reserved_size; }

	void				set_delete_mode(DeleteMode mode);
	DeleteMode			get_delete_mode() { return m_delete_mode; }

private:
	void *				m_buffer;

	size_t				m_size;
	size_t				m_reserved_size;

	DeleteMode			m_delete_mode;
};

typedef std::shared_ptr<Buffer> BufferPtr;
#define AeonEmptyBuffer BufferPtr()

} //namespace Aeon

#endif // AeonBuffer_h__
