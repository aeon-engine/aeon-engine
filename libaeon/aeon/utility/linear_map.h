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

template <typename key_type, typename value_type>
class linear_map
{
public:
    using pair_type = std::pair<key_type, value_type>;
    using map_type = std::vector<pair_type>;

    linear_map()
    {
    }

    ~linear_map()
    {
    }

    typename map_type::iterator insert(const key_type &key, const value_type &value)
    {
        return insert(std::make_pair(key, value));
    }

    typename map_type::iterator insert(pair_type pair)
    {
        auto itr = __find_key(pair.first);

        if (itr == map_.end())
            return map_.insert(map_.end(), pair);

        itr->second = pair.second;
        return itr;
    }

    typename map_type::iterator insert_ex(const key_type &key, const value_type &value)
    {
        return insert_ex(std::make_pair(key, value));
    }

    typename map_type::iterator insert_ex(pair_type pair)
    {
        auto itr = __find_key(pair.first);

        if (itr == map_.end())
            return map_.insert(map_.end(), pair);

        return map_.end();
    }

    value_type &at(const key_type &key)
    {
        auto itr = __find_key(key);
        if (itr == map_.end())
            throw std::out_of_range("aeon linear_map key out of range.");

        return itr->second;
    }

    value_type &operator[](const key_type &key)
    {
        auto itr = __find_key(key);

        if (itr == map_.end())
            itr = insert(key, value_type());

        return itr->second;
    }

    typename map_type::iterator find(const key_type &key)
    {
        return __find_key(key);
    }

    typename map_type::iterator begin() noexcept
    {
        return map_.begin();
    }

    typename map_type::iterator end() noexcept
    {
        return map_.end();
    }

    typename map_type::const_iterator begin() const noexcept
    {
        return map_.cbegin();
    }

    typename map_type::const_iterator end() const noexcept
    {
        return map_.cend();
    }

    typename map_type::iterator erase(const key_type &key)
    {
        auto itr = __find_key(key);

        if (itr != map_.end())
            return erase(itr);

        return itr;
    }

    void erase_if(std::function<bool(const pair_type &)> pred)
    {
        for (auto obj = map_.begin(); obj != map_.end();)
        {
            if (pred(*obj))
            {
                obj = map_.erase(obj);
            }
            else
            {
                ++obj;
            }
        }
    }

    typename map_type::iterator erase(typename map_type::iterator itr)
    {
        return map_.erase(itr);
    }

    bool empty() const
    {
        return map_.empty();
    }

    void clear()
    {
        map_.clear();
    }

    std::size_t size() const noexcept
    {
        return map_.size();
    }

private:
    typename map_type::iterator __find_key(const key_type &key)
    {
        typename map_type::iterator itr =
            std::find_if(map_.begin(), map_.end(), [key](const pair_type &s) { return s.first == key; });

        return itr;
    }

    map_type map_;
};

} // namespace utility
} // namespace aeon
