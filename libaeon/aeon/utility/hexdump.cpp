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

#include <aeon/utility.h>

namespace aeon
{
namespace utility
{

void hexdump(FILE *dest, const void *src, std::size_t len)
{
    fputs("--------|------------------------------------------------|----------------|\n", dest);
    fputs(" offset |00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F |0123456789ABCDEF|\n", dest);
    fputs("--------|------------------------------------------------|----------------|\n", dest);

    std::size_t i = 0;
    std::size_t c = 0;
    const unsigned char *pData = reinterpret_cast<const unsigned char *>(src);

    for (; i < len;)
    {
        std::size_t start = i;
        fprintf(dest, "%08X|", static_cast<unsigned int>(i));
        for (c = 0; c < 16 && i < len;) // write 16 bytes per line
        {
            fprintf(dest, "%02X ", static_cast<int>(pData[i]));
            ++i;
            ++c;
        }

        std::size_t written = c;
        for (; c < 16; ++c) // finish off any incomplete bytes
            fputs("   ", dest);

        // write the text part
        fputc('|', dest);
        for (c = 0; c < written; ++c)
        {
            std::uint8_t byte = pData[start + c];
            if (isprint(static_cast<int>(byte)))
                fputc(static_cast<char>(byte), dest);
            else
                fputc('.', dest);
        }

        for (; c < 16; ++c)
            fputc(' ', dest);

        fputs("|\n", dest);
    }

    fputs("---------------------------------------------------------------------------\n", dest);
}

} // namespace utility
} // namespace aeon
