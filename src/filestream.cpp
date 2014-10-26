/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2014 Robin Degen
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

file_stream::file_stream(const std::string &path, 
                         int mode /*= access_mode::read*/) :
    stream(path, mode),
    file_(nullptr)
{
    if (mode == (access_mode::read | access_mode::write))
    {
        console::error("[FileStream]: Invalid access mode: "
            "Read+Write on file %s.", name_.c_str());
        return;
    }

    __open_file();
}

file_stream::~file_stream()
{
}

void file_stream::__open_file()
{
    if (access_mode_ == access_mode::read)
        file_ = fopen(name_.c_str(), "rb");
    else
        file_ = fopen(name_.c_str(), "wb");

    if (!file_)
    {
        console::error("[FileStream]: Could not open file: %s", name_.c_str());
        return;
    }

    if(access_mode_ == access_mode::read)
        __calculate_file_size();
}

void file_stream::__calculate_file_size()
{
    if (!file_)
    {
        console::error("[FileStream]: Size requested on unopened file.");
        return;
    }

    if (!seek(0, seek_direction::end))
        console::error("[FileStream]: Could not determine file size for file: "
            "%s. Seek end failed.", name_.c_str());

    size_ = ftell(file_);

    if (size_ == 0)
        console::warning("[FileStream]: File is empty: %s", name_.c_str());

    if (!seek(0, seek_direction::begin))
        console::error("[FileStream]: Could not determine file size for file: "
            "%s. Seek begin failed.", name_.c_str());
}

size_t file_stream::read(void *buffer, size_t count)
{
    if (!file_)
    {
        console::error("[FileStream]: Read on unopened file.");
        return 0;
    }

    if (access_mode_ != access_mode::read)
    {
        console::error("[FileStream]: Can not read from file in write mode "
            "for file %s.", name_.c_str());
        return 0;
    }

    if (!buffer)
    {
        console::error("[FileStream]: Input buffer is NULL.");
        return 0;
    }

    if (count == 0)
    {
        console::warning("[FileStream]: Tried writing 0 bytes.");
        return 0;
    }

    return fread(buffer, 1, count, file_);
}

bool file_stream::read(std::uint8_t &data)
{
    if (access_mode_ != access_mode::read)
    {
        console::error("[FileStream]: Can not read from file in write mode "
            "for file %s.", name_.c_str());
        return false;
    }

    int c = fgetc(file_);

    if (c == EOF)
        return false;

    data = (std::uint8_t) c;
    return true;
}

bool file_stream::peek(std::uint8_t &data)
{
    if (access_mode_ != access_mode::read)
    {
        console::error("[FileStream]: Can not peek from file in write mode "
            "for file %s.", name_.c_str());
        return false;
    }

    int c = fgetc(file_);

    if (c == EOF)
        return false;

    // TODO: research if there is a good alternative for this.
    if (ungetc(c, file_) == EOF)
        return false;

    data = (std::uint8_t) c;
    return true;
}

size_t file_stream::write(const void *buffer, size_t count)
{
    if (!file_)
    {
        console::error("[FileStream]: Write on unopened file.");
        return 0;
    }

    if (access_mode_ != access_mode::write)
    {
        console::error("[FileStream]: Can not write to file in read mode "
            "for file %s.", name_.c_str());
        return 0;
    }

    if (!buffer)
    {
        console::error("[FileStream]: Input buffer is NULL.");
        return 0;
    }

    if (count == 0)
    {
        console::warning("[FileStream]: Tried writing 0 bytes.");
        return 0;
    }

    return fwrite(buffer, 1, count, file_);
}

bool file_stream::seek(size_t pos, seek_direction direction)
{
    if (!file_)
    {
        console::error("[FileStream]: Seek on unopened file.");
        return false;
    }

    switch (direction)
    {
        case seek_direction::begin:
        {
            return fseek(file_, (long) pos, SEEK_SET) == 0;
        }break;
        case seek_direction::current:
        {
            return fseek(file_, (long) pos, SEEK_CUR) == 0;
        }break;
        case seek_direction::end:
        {
            return fseek(file_, (long) pos, SEEK_END) == 0;
        }break;
    };

    return false;
}

size_t file_stream::tell() const
{
    if(!file_)
    {
        console::error("[FileStream]: Tell on unopened file.");
        return 0;
    }

    return ftell(file_);
}

bool file_stream::eof() const
{
    if(!file_)
    {
        console::error("[FileStream]: EOF on unopened file.");
        return true;
    }

    return (feof(file_) != 0);
}

void file_stream::close()
{
    if(!file_)
    {
        console::error("[FileStream]: Close on unopened file.");
        return;
    }

    console::debug("[FileStream]: Closing file stream.");

    fclose(file_);
    file_ = nullptr;
}

void file_stream::flush()
{
    if(!file_)
    {
        console::error("[FileStream]: Close on unopened file.");
        return;
    }

    fflush(file_);
}

bool file_stream::good()
{
    return file_ != nullptr;
}

} /* namespace Aeon */
