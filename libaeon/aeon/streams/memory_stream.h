/*
 * Copyright (c) 2012-2017 Robin Degen
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

namespace aeon
{
namespace streams
{

class memory_stream_exception : public stream_exception
{
};

class memory_stream : public stream
{
public:
    memory_stream()
        : stream(access_mode::read_write)
        , offset_(0)
        , size_(0)
    {
    }

    explicit memory_stream(std::vector<std::uint8_t> &&buffer, int mode = access_mode::read_write)
        : stream(mode)
        , buffer_(std::move(buffer))
        , offset_(0)
        , size_(0)
    {
        size_ = buffer_.size();
    }

    virtual ~memory_stream() = default;

    memory_stream(memory_stream &&o) = default;
    memory_stream &operator=(memory_stream &&other) = default;

    std::size_t read(std::uint8_t *data, std::size_t size) override
    {
        if (!is_readable())
            throw memory_stream_exception();

        if (!data || size == 0)
            throw memory_stream_exception();

        // Only read what we have
        if (offset_ + size > size_)
            size = size_ - offset_;

        // Are we really out of bounds?
        if (size == 0)
            return 0;

        // Copy our data
        std::memcpy(data, &buffer_[offset_], size);
        offset_ += size;

        return size;
    }

    std::size_t write(const std::uint8_t *data, std::size_t size) override
    {
        if (!is_writable())
            throw memory_stream_exception();

        if (!data || size == 0)
            throw memory_stream_exception();

        // Make sure we have enough space in the buffer
        reserve(offset_ + size);

        // Copy our data
        std::memcpy(&buffer_[offset_], data, size);
        offset_ += size;

        return size;
    }

    bool peek(std::uint8_t &data, std::ptrdiff_t offset = 0) override
    {
        if (!is_readable() || !good())
            throw memory_stream_exception();

        if (offset_ + offset >= size_)
            return false;

        data = buffer_[offset_ + offset];
        return true;
    }

    bool seek(std::ptrdiff_t pos, stream::seek_direction direction) override
    {
        std::ptrdiff_t new_pos = 0;
        switch (direction)
        {
            case seek_direction::begin:
            {
                new_pos = pos;
            }
            break;
            case seek_direction::current:
            {
                new_pos = offset_ + pos;
            }
            break;
            case seek_direction::end:
            {
                new_pos = (size_ - 1) - pos;
            }
            break;
        };

        // Can't go higher then the size of our buffer...
        if (new_pos < 0)
            return false;

        if (new_pos >= static_cast<std::ptrdiff_t>(size_))
            return false;

        // Set the new offset if all is good
        offset_ = new_pos;
        return true;
    }

    bool seekw(std::ptrdiff_t /* pos */, stream::seek_direction /* direction */) override
    {
        return false;
    }

    std::size_t tell() override
    {
        return offset_;
    }

    std::size_t tellw() override
    {
        return 0;
    }

    bool eof() const override
    {
        return offset_ >= size_;
    }

    std::size_t size() const override
    {
        return size_;
    }

    void flush() override
    {
    }

    bool good() const override
    {
        // If the buffer is empty, and we haven't written anything, we're ok.
        if (offset_ == 0 && buffer_.empty())
            return true;

        // Are we still within bounds?
        if (offset_ >= buffer_.size())
            return false;

        // All ok!
        return true;
    }

    void reserve(std::size_t size)
    {
        if (size > buffer_.size())
            buffer_.resize(buffer_.size() + size);

        if (size > size_)
            size_ = size;
    }

    void expand(std::size_t size)
    {
        reserve(buffer_.size() + size);
    }

    std::uint8_t *data()
    {
        return &buffer_[0];
    }

    std::vector<std::uint8_t> read_to_vector() override
    {
        return buffer_;
    }

protected:
    std::vector<std::uint8_t> buffer_;
    std::size_t offset_;
    std::size_t size_;
};

typedef std::shared_ptr<memory_stream> memory_stream_ptr;

} // namespace streams
} // namespace aeon
