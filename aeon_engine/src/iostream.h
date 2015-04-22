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

class io_stream : public aeon::streams::stream
{
public:
    io_stream(int mode = aeon::streams::access_mode::read);

    virtual ~io_stream();

    virtual std::size_t read(std::uint8_t *data, std::size_t size);

    virtual std::size_t write(const std::uint8_t *data, std::size_t size);

    virtual bool peek(std::uint8_t &data, std::ptrdiff_t offset = 0);

    virtual bool seek(std::ptrdiff_t pos, seek_direction direction);

    virtual bool seekw(std::ptrdiff_t pos, seek_direction direction);

    virtual std::size_t tell();

    virtual std::size_t tellw();

    virtual bool eof() const;

    virtual std::size_t size() const;

    virtual void flush();

    virtual bool good() const;
};

} // namespace aeon

#endif // iostream_h__
