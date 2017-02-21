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
namespace utility
{

// Simple wrapper to convert a vector of strings to a char*[].
class parameters : noncopyable
{
public:
    explicit parameters(std::vector<std::string> &params)
        : argc_(0)
        , argv_(new char *[params.size()])
    {
        for (auto &param : params)
        {
            argv_[argc_] = new char[param.size() + 1];
            memcpy(argv_[argc_], param.data(), param.size() + 1);
            ++argc_;
        }
    }

    ~parameters()
    {
        if (!argv_)
            return;

        for (int i = 0; i < argc_; ++i)
        {
            delete[] argv_[i];
        }

        delete[] argv_;
    }

    parameters(parameters &&other)
        : argc_(std::move(other.argc_))
        , argv_(std::move(other.argv_))
    {
        other.argc_ = 0;
        other.argv_ = nullptr;
    }

    parameters &operator=(parameters &&other)
    {
        argc_ = std::move(other.argc_);
        argv_ = std::move(other.argv_);
        other.argc_ = 0;
        other.argv_ = nullptr;
        return *this;
    }

    int argc() const
    {
        return argc_;
    }

    const char *const *argv() const
    {
        return argv_;
    }

private:
    int argc_;
    char **argv_;
};

} // namespace utility
} // namespace aeon
