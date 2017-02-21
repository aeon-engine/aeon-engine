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

class variant
{
public:
    enum class variant_type
    {
        variant_nil,
        variant_int,
        variant_float,
        variant_bool,
        variant_string
    };

    variant()
        : int_value_(0)
        , float_value_(0.0f)
        , bool_value_(false)
        , string_value_("")
        , type_(variant_type::variant_nil)
    {
    }

    variant(const int &value)
        : int_value_(value)
        , float_value_(static_cast<float>(value))
        , bool_value_(value >= 0)
        , string_value_(std::to_string(value))
        , type_(variant_type::variant_int)
    {
    }

    variant(const float &value)
        : int_value_(static_cast<int>(value))
        , float_value_(value)
        , bool_value_(value >= 0.0f)
        , string_value_(std::to_string(value))
        , type_(variant_type::variant_float)
    {
    }

    variant(const bool &value)
        : int_value_(value == false ? 0 : 1)
        , float_value_(value == false ? 0.0f : 1.0f)
        , bool_value_(value)
        , string_value_(value == false ? "false" : "true")
        , type_(variant_type::variant_bool)
    {
    }

    variant(const std::string &value)
        : int_value_(0)
        , float_value_(0)
        , bool_value_(false)
        , string_value_(value)
        , type_(variant_type::variant_string)
    {
        if (value == "true")
        {
            int_value_ = 1;
            float_value_ = 1.0f;
            bool_value_ = true;
        }
        else if (value == "false")
        {
            int_value_ = 0;
            float_value_ = 0.0f;
            bool_value_ = false;
        }
        else
        {
            try
            {
                float_value_ = std::stof(string_value_);
                int_value_ = static_cast<int>(float_value_);
                bool_value_ = float_value_ >= 0.0;
            }
            catch (std::exception &)
            {
                float_value_ = 0.0f;
                int_value_ = 0;
                bool_value_ = false;
            }
        }
    }

    const int &int_value() const
    {
        return int_value_;
    }

    const float &float_value() const
    {
        return float_value_;
    }

    const bool &bool_value() const
    {
        return bool_value_;
    }

    const std::string &string_value() const
    {
        return string_value_;
    }

    const variant_type &type() const
    {
        return type_;
    }

private:
    int int_value_;
    float float_value_;
    bool bool_value_;
    std::string string_value_;
    variant_type type_;
};

} // namespace utility
} // namespace aeon
