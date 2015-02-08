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

#ifndef iostream_h__
#define iostream_h__

namespace aeon
{

class io_stream : public stream
{
public:
    io_stream(int mode = access_mode::read);
    io_stream(const std::string &name, int mode = access_mode::read);

    virtual size_t read(void *buffer, size_t count);
    virtual size_t write(const void *buffer, size_t count);

    virtual bool read(std::uint8_t &data);
    virtual bool peek(std::uint8_t &data);

    virtual bool seek(size_t pos, seek_direction direction);
    virtual size_t tell() const;

    virtual bool eof() const;

    virtual void flush();

    virtual bool good() { return true; }

    virtual buffer_ptr get_as_buffer();
};

} /* namespace aeon */

#endif /* iostream_h__ */
