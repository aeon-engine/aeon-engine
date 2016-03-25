#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cstdint>

#include <common/buffer.h>

namespace aeon
{
namespace audio
{
class base_buffer
{
public:
    virtual const uint8_t *data() const = 0;
    virtual bool empty() const = 0;
    virtual size_t size() const = 0;

    // some hacks so we can facilitate reading ogg files
    virtual size_t read(void *data, size_t size, size_t nmemb) = 0;
    virtual int seek(int64_t offset, int whence) = 0;
    virtual int64_t tell() = 0;
};

/* this is a hack, its also a plain copy of the file_buffer class. The only
 * thing we need todo right here is to make the file_buffer class deriving of
 * the memory_buffer class. This way we can get rid of the mess and stuff.
 */
class memory_buffer : public base_buffer
{
public:
    memory_buffer()
        : base_buffer()
        , read_offset_(0)
    {
    }

    explicit memory_buffer(common::buffer_u8 &data)
        : base_buffer()
        , read_offset_(0)
    {
        buffer_.resize(data.size());
        memcpy(buffer_.data(), data.data(), buffer_.size());
    }

    explicit memory_buffer(common::buffer_u8 &&data)
        : base_buffer()
        , buffer_(std::move(data))
        , read_offset_(0)
    {
    }

    const uint8_t *data() const override
    {
        return buffer_.data();
    }

    bool empty() const override
    {
        return buffer_.empty();
    }

    size_t size() const override
    {
        return buffer_.size();
    }

    /* \todo handle all the error cases */
    size_t read(void *data, size_t size, size_t nmemb) override
    {
        if (read_offset_ >= (int64_t)buffer_.size())
            return 0;

        // the amount of bytes we can maximum read.
        int64_t bytes_available = buffer_.size() - read_offset_;
        // the amount of bytes we want to read
        int64_t bytes_want = size * nmemb;
        // the amount of bytes we can read
        int64_t bytes_can_read = std::min(bytes_available, bytes_want);

        if (bytes_can_read == 0)
        {
            printf("aeon::audio::codec_file, bytes can read == 0\n");
            return 0;
        }

        memcpy(data, &buffer_[read_offset_], bytes_can_read);
        read_offset_ += bytes_can_read;

        return bytes_can_read;
    }

    /* if successful we return 0 here, otherwise we return -1 */
    int seek(int64_t offset, int origin) override
    {
        switch (origin)
        {
        case SEEK_SET:

            if (offset <= (int64_t)buffer_.size()) // blegh c style cast
            {
                read_offset_ = offset;
            }
            else
            {
                printf("aeon::audio::codec_file, seek error case SET\n");
                return -1;
            }
            break;
        case SEEK_CUR:
            if (read_offset_ + offset <= (int64_t)buffer_.size()) //blegh cast
            {
                read_offset_ += offset;
            }
            else
            {
                printf("aeon::audio::codec_file, seek error case CUR\n");
                return -1;
            }
            break;
        case SEEK_END:
        {
            int64_t new_offset = buffer_.size();
            new_offset -= offset;

            if ((int64_t)buffer_.size() - offset >= 0) //blegh cast
            {
                read_offset_ = buffer_.size() - offset;
            }
            else
            {
                printf("aeon::audio::codec_file, seek error case END\n");
                return -1;
            }
        } break;
        default:
            return -1;
            break;
        }
        return 0;
    }

    int64_t tell() override
    {
        return read_offset_;
    }
private:
    common::buffer_u8 buffer_;
    int64_t read_offset_; // we only allow to read in a audio codec file buffer
};

/* THIS IS A HACK BECAUSE I AM TO LAZY TO USE ANYTHING ELSE */
class file_buffer : public base_buffer
{
public:
    file_buffer()
        : base_buffer()
        , filename_()
        , read_offset_(0)
    {
    }

    explicit file_buffer(std::string filepath)
        : base_buffer()
        , filename_(filepath)
        , read_offset_(0)
    {
        open_and_read();
    }

    void open_and_read()
    {
        FILE *fp;
        /* fopen_s is not a Microsoft idea but actually part of C11  */
        fopen_s(&fp, filename_.c_str(), "rb");
        if (!fp)
        {
            printf("aeon::audio::file_buffer, unable to open file\n");
            return;
        }

        fseek(fp, 0, SEEK_END);
        size_t fsize = ftell(fp);
        fseek(fp, 0, SEEK_SET);

        buffer_.resize(fsize); // this will throw if resize fails and cause 'fp' to leak.

        fread(buffer_.data(), fsize, 1, fp);
        fclose(fp);
    }

    const uint8_t *data() const final
    {
        return buffer_.data();
    }

    bool empty() const final
    {
        return buffer_.empty();
    }

    size_t size() const final
    {
        return buffer_.size();
    }

    /* \todo handle all the error cases */
    size_t read(void *data, size_t size, size_t nmemb) final
    {
        if (read_offset_ >= (int64_t)buffer_.size())
            return 0;

        // the amount of bytes we can maximum read.
        int64_t bytes_available = buffer_.size() - read_offset_;
        // the amount of bytes we want to read
        int64_t bytes_want = size * nmemb;
        // the amount of bytes we can read
        int64_t bytes_can_read = std::min(bytes_available, bytes_want);

        if (bytes_can_read == 0)
        {
            printf("aeon::audio::codec_file, bytes can read == 0\n");
            return 0;
        }

        memcpy(data, &buffer_[read_offset_], bytes_can_read);
        read_offset_ += bytes_can_read;

        return bytes_can_read;
    }

    /* if successful we return 0 here, otherwise we return -1 */
    int seek(int64_t offset, int origin) final
    {
        switch (origin)
        {
        case SEEK_SET:

            if (offset <= (int64_t)buffer_.size()) // blegh c style cast
            {
                read_offset_ = offset;
            }
            else
            {
                printf("aeon::audio::codec_file, seek error case SET\n");
                return -1;
            }
            break;
        case SEEK_CUR:
            if (read_offset_ + offset <= (int64_t)buffer_.size()) //blegh cast
            {
                read_offset_ += offset;
            }
            else
            {
                printf("aeon::audio::codec_file, seek error case CUR\n");
                return -1;
            }
            break;
        case SEEK_END:
        {
            int64_t new_offset = buffer_.size();
            new_offset -= offset;

            if ((int64_t)buffer_.size() - offset >= 0) //blegh cast
            {
                read_offset_ = buffer_.size() - offset;
            }
            else
            {
                printf("aeon::audio::codec_file, seek error case END\n");
                return -1;
            }
        } break;
        default:
            return -1;
            break;
        }
        return 0;
    }

    int64_t tell() final
    {
        return read_offset_;
    }

    common::buffer_u8 &buffer()
    {
        return buffer_;
    }

private:
    std::string filename_;
    common::buffer_u8 buffer_;
    int64_t read_offset_; // we only allow to read in a audio codec file buffer
};
} // namespace audio
} // namespace aeon
