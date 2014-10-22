#ifndef buffer_h__
#define buffer_h__

namespace aeon
{

/*!
 * \brief Wrapper class for memory buffers
 *
 * This class serves as a memory buffer wrapper. This makes working with 
 * buffers much easier, helping to prevent memory leaks.
 */
class buffer
{
public:
    /*!
     * The delete mode for a Buffer. This determines if the internal buffer is 
     * automatically deleted in the destructor.
     */
    enum class delete_mode
    {
        none,
        delete_on_destruct
    };

    /*!
     * Construct an empty buffer. This constructor is merely used to construct 
     * an empty container that can be used to allocate memory later.
     */
    buffer();

    /*!
     * Create a buffer of size bytes. If delete_mode is set to 
     * DeleteMode::None, this internal buffer will not be freed. Be sure to 
     * get() this pointer and free it yourself to prevent memory leaks.
     *
     * The internal buffer is created using malloc, this means you must free 
     * this buffer. Do not use delete [].
     *
     * \param size The size of the buffer to be allocated
     * \param delete_mode Determines if the internal buffer should be 
     *                    automatically freed or not.
     * \sa DeleteMode
     */
    buffer(size_t size, delete_mode mode = delete_mode::delete_on_destruct);

    /*!
     * Wrap around a buffer of size bytes. If delete_mode is set to 
     * DeleteMode::None, this buffer will not be freed. Be sure to free it 
     * yourself to prevent memory leaks.
     *
     * The buffer pointer must have been allocated using malloc in order to 
     * use reserve, resize, append, DeleteMode::DeleteOnDestruct, etc.
     *
     * \param buffer The buffer to wrap around
     * \param size The size of the buffer
     * \param delete_mode Determines if the internal buffer should be 
     *                    automatically freed or not.
     * \sa DeleteMode 
     */
    buffer(void *buffer, size_t size, 
        delete_mode mode = delete_mode::delete_on_destruct);

    /*!
     * Destructor
     *
     * If the DeleteMode is set to DeleteMode::DeleteOnDestruct, the buffer 
     * will be automatically freed.
     */
    ~buffer();

    /*!
     * Prevent copying this class.
     */
    buffer(const buffer&) = delete;

    /*!
     * Prevent copying this class.
     */
    buffer & operator=(const buffer&) = delete;

    /*!
     * Allocate at least n bytes
     */
    bool reserve(size_t n);

    /*!
     * Resize to the specified size.
     */
    bool resize(size_t n);

    bool append(void *data, size_t len);

    void free();

    void *get() { return buffer_; }

    size_t size() { return size_; }
    size_t reserved_size() { return reserved_size_; }

    void set_delete_mode(delete_mode mode);
    delete_mode get_delete_mode() { return delete_mode_; }

    void set_size(size_t size) { size_ = size; }

private:
    void *buffer_;

    size_t size_;
    size_t reserved_size_;

    delete_mode delete_mode_;
};

typedef std::shared_ptr<buffer> buffer_ptr;
#define aeon_empty_buffer buffer_ptr()

} /* namespace aeon */

#endif /* buffer_h__ */
