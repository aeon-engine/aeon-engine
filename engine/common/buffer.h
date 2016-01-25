/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2016 Robin Degen
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

#pragma once

#include <memory>
#include <vector>
#include <cstdint>

namespace aeon
{
namespace common
{

template <typename T>
using buffer = std::vector<T>;

using buffer_u8 = buffer<std::uint8_t>;
using buffer_pu8 = buffer<std::uint8_t *>;

template <typename T>
using buffer_ptr = std::shared_ptr<buffer<T>>;

using buffer_ptr_u8 = buffer_ptr<std::uint8_t>;

} // namespace common
} // namespace aeon
