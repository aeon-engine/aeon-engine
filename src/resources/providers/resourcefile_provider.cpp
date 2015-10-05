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

#include <resources/providers/resourcefile_provider.h>

namespace aeon
{
namespace resources
{

resourcefile_provider::resourcefile_provider(const std::string &base_path)
{
    throw resourcefile_provider_not_implemented_exception();
}

resourcefile_provider::~resourcefile_provider()
{
}

bool resourcefile_provider::exists(const std::string &path)
{
    throw resourcefile_provider_not_implemented_exception();
}

std::vector<resource_node> resourcefile_provider::list(const std::string &path)
{
    throw resourcefile_provider_not_implemented_exception();
}

void resourcefile_provider::read(const std::string &path, common::buffer_u8 &buffer)
{
    throw resourcefile_provider_not_implemented_exception();
}

resource_encoding resourcefile_provider::get_encoding(const std::string &path) const
{
    throw resourcefile_provider_not_implemented_exception();
}

} // namespace resources
} // namespace aeon
