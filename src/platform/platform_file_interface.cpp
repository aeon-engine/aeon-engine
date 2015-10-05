/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2015 Robin Degen
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

#include <platform/platform_file_interface.h>
#include <platform/platform_filesystem_interface.h>

namespace aeon
{
namespace platform
{

platform_file_interface::platform_file_interface(const std::string &path, int openmode) :
    openmode_(openmode),
    path_(path)
{
}

platform_file_interface::~platform_file_interface()
{
}

} // namespace platform
} // namespace aeon
