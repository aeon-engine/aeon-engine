#ifndef filestream_h__
#define filestream_h__

#include "aeon/streams/stream.h"

namespace aeon
{

class file_stream : public stream
{
public:
    file_stream(const std::string &path, int mode = access_mode::read);
    virtual ~file_stream();

    virtual size_t read(void *buffer, size_t count);
    virtual size_t write(const void *buffer, size_t count);

    virtual bool read(std::uint8_t &data);
    virtual bool peek(std::uint8_t &data);

    virtual bool seek(size_t pos, seek_direction direction);
    virtual size_t tell() const;

    virtual bool eof() const;

    virtual void close();

    virtual void flush();

    virtual bool good();

protected:
    void __open_file();
    void __calculate_file_size();

    FILE *file_;
};

typedef std::shared_ptr<file_stream> file_stream_ptr;

} /* namespace aeon */

#endif /* filestream_h__ */
