/*
 * Copyright (c) 2012-2018 Robin Degen
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

#include <array>
#include <cstddef>
#include <cstring>

namespace aeon
{
namespace input
{

template <typename key_t, typename state_t, std::size_t size>
class input_state
{
public:
    explicit input_state(const state_t default_state)
    {
        for (auto i = 0; i < size; ++i)
        {
            state_[i] = default_state;
            first_of_frame_[i] = false;
        }
    }

    void update_state(const key_t key, const state_t state)
    {
        const auto key_index = static_cast<std::size_t>(key);
        auto &s = state_[key_index];

        if (s != state)
            first_of_frame_[key_index] = true;

        s = state;
    }

    auto get_state(const key_t key) const
    {
        const auto key_index = static_cast<std::size_t>(key);
        return state_[key_index];
    }

    auto get_frame_state(const key_t key, const state_t state) const
    {
        const auto key_index = static_cast<std::size_t>(key);
        auto &input_state = state_[key_index];

        if (!first_of_frame_[key_index])
            return false;

        return input_state == state;
    }

    auto is_any_in_state(const state_t state) const
    {
        for (auto i = 0; i < size; ++i)
        {
            if (state_[i] == state)
                return true;
        }

        return false;
    }

    void reset_first_of_frame()
    {
        memset(first_of_frame_.data(), 0, size * sizeof(bool));
    }

private:
    std::array<state_t, size> state_;
    std::array<bool, size> first_of_frame_;
};

} // namespace input
} // namespace aeon
