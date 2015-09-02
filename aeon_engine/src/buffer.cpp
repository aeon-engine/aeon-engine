/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2015 Robin Degen
 * All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains the property of
 * Robin Degen and its suppliers, if any. The intellectual and technical
 * concepts contained herein are proprietary to Robin Degen and its suppliers
 * and may be covered by U.S. and Foreign Patents, patents in process, and are
 * protected by trade secret or copyright law. Dissemination of this
 * information or reproduction of this material is strictly forbidden unless
 * prior written permission is obtained from Robin Degen.
 */

#include "stdafx.h"

namespace aeon
{

buffer::buffer() :
    buffer_(nullptr),
    size_(0),
    reserved_size_(0),
    delete_mode_(delete_mode::delete_on_destruct)
{
}

buffer::buffer(size_t size, 
               delete_mode mode /*= delete_mode::delete_on_destruct*/) :
    buffer_(nullptr),
    size_(size),
    reserved_size_(size),
    delete_mode_(mode)
{
    resize(size);
}

buffer::buffer(void *buffer, size_t size, 
               delete_mode mode /*= delete_mode::delete_on_destruct*/) :
    buffer_(buffer),
    size_(size),
    reserved_size_(size),
    delete_mode_(mode)
{
    resize(size);
}

buffer::~buffer()
{
    if (delete_mode_ == delete_mode::delete_on_destruct)
        free();
}

bool buffer::reserve(size_t n)
{
    // Do we already have this many bytes reserved?
    if (n <= reserved_size_)
        return true;

    // Resize the array if we're requesting more bytes
    bool result = resize(n);

    if(result)
        console::debug("[Buffer]: Reserved %u bytes at %p.", n, buffer_);

    return result;
}

bool buffer::resize(size_t n)
{
    // Reallocate the buffer to be the new size
    void *new_buffer = realloc(buffer_, n);

    // Did we fail to reallocate our buffer?
    if (!new_buffer)
    {
        // Do we have data at all?
        if (buffer_)
        {
            console::warning("[Buffer]: Failed to reallocate buffer from "
                "%u to %u. Trying copy.", reserved_size_, n);

            // Try a fallback method...
            new_buffer = malloc(n);

            // Did we fail again?!
            if (!new_buffer)
            {
                console::error("[Buffer]: Failed to reallocate buffer from "
                    "%u to %u in fallback mode. Aborting", reserved_size_, n);
                return false;
            }

            // How many bytes do we need to copy? 
            // Are we increasing or shrinking?
            size_t newsize = (n < reserved_size_) ? n : reserved_size_;

            // All ok! Lets copy!
            memcpy(new_buffer, buffer_, newsize);

            // Free the old buffer
            ::free(buffer_);

            buffer_ = new_buffer;

            return true;
        }

        console::error("[Buffer]: Could not allocate buffer for %u bytes.", n);
        return false;
    }

    // All is ok! Let's keep our new data
    buffer_ = new_buffer;
    reserved_size_ = n;

    return true;
}

bool buffer::append(void *data, size_t len)
{
    // Does our appended data fit?
    if (size_ + len > reserved_size_)
    {
        // Make sure our buffer is able to fit this data
        if (!reserve(reserved_size_ + len))
            return false;
    }

    // Copy our data into the new buffer
    char *buff = static_cast<char *>(buffer_);
    memcpy(&buff[size_], data, len);

    // Adjust the size
    size_ += len;

    return true;
}

void buffer::free()
{
    ::free(buffer_);

    console::debug("[Buffer]: Freed %u bytes from %p.", 
        reserved_size_, buffer_);

    buffer_ = nullptr;
    size_ = 0;
    reserved_size_ = 0;
}

void buffer::set_delete_mode(delete_mode mode)
{
    delete_mode_ = mode;
}

} // namespace aeon
