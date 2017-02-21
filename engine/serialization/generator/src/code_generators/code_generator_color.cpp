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

#include <code_generators/code_generator_color.h>
#include <aeon/utility.h>
#include <string>

namespace aeon
{
namespace serialization
{

auto code_generator_color::get_type_name() const -> std::string
{
    return "color";
}

auto code_generator_color::generate_required_header_includes() const -> std::set<std::string>
{
    return {"aeon/common/types/color.h"};
}

auto code_generator_color::generate_cpp_type_name() const -> std::string
{
    return "aeon::utility::optional<aeon::common::types::color>";
}

auto code_generator_color::generate_cpp_array_type_name() const -> std::string
{
    return "std::vector<aeon::common::types::color>";
}

auto code_generator_color::generate_deserialization_code(const object_member &object_member) const -> std::string
{
    std::string code = R"code(
    auto %member_name%_array_items = json["%member_name%"].array_items();

    if (!%member_name%_array_items.empty())
    {
        %member_name% = aeon::common::types::color(
            static_cast<float>(%member_name%_array_items[0].number_value()),
            static_cast<float>(%member_name%_array_items[1].number_value()),
            static_cast<float>(%member_name%_array_items[2].number_value()),
            static_cast<float>(%member_name%_array_items[3].number_value()));
    }
)code";

    utility::string::replace(code, "%member_name%", object_member.get_name());
    return code;
}

auto code_generator_color::generate_array_deserialization_code(const object_member &object_member) const -> std::string
{
    std::string code = R"code(
    auto %member_name%_array = json["%member_name%"];

    if (%member_name%_array.is_array())
    {
        for (auto &%member_name%_array_item : %member_name%_array.array_items())
        {
            auto %member_name%_array_color_items = %member_name%_array_item.array_items();
            if (!%member_name%_array_color_items.empty())
            {
                %member_name%.push_back(aeon::common::types::color(
                    static_cast<float>(%member_name%_array_color_items[0].number_value()),
                    static_cast<float>(%member_name%_array_color_items[1].number_value()),
                    static_cast<float>(%member_name%_array_color_items[2].number_value()),
                    static_cast<float>(%member_name%_array_color_items[3].number_value())));
            }
        }
    }
)code";

    utility::string::replace(code, "%member_name%", object_member.get_name());
    return code;
}

auto code_generator_color::generate_serialization_code(const object_member &object_member) const -> std::string
{
    std::string code = R"code(
    if (%member_name%.has_value())
    {
        auto %member_name%_value = %member_name%.get_value();
        json_obj["%member_name%"] = json11::Json::array { %member_name%_value.r, %member_name%_value.g, %member_name%_value.b, %member_name%_value.a };
    }
)code";
    utility::string::replace(code, "%member_name%", object_member.get_name());
    return code;
}

auto code_generator_color::generate_array_serialization_code(const object_member &object_member) const -> std::string
{
    std::string code = R"code(
    json11::Json::array %member_name%_item_array;
    for (auto &%member_name%_item : %member_name%)
    {
        %member_name%_item_array.push_back(json11::Json::array{ %member_name%.r, %member_name%.g, %member_name%.b, %member_name%.a });
    }

    json_obj[%member_name%"] = json11::Json::array { %member_name%_item_array };
)code";

    utility::string::replace(code, "%member_name%", object_member.get_name());
    return code;
}

} // namespace serialization
} // namespace aeon
