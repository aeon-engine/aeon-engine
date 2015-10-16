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

#include <common/exception.h>

namespace aeon
{
namespace resources
{

DEFINE_EXCEPTION_OBJECT(resource_exception, aeon::common::exception,
    "Generic resource exception.");

// resource_manager
DEFINE_EXCEPTION_OBJECT(resource_manager_exception, resource_exception,
    "Generic resource manager exception.");

DEFINE_EXCEPTION_OBJECT(resource_manager_mount_exception, resource_manager_exception,
    "Could not mount resource provider.");

DEFINE_EXCEPTION_OBJECT(resource_manager_duplicate_mount_exception, resource_manager_mount_exception,
    "Could not mount resource provider. Duplicate mountpoint given.");

// resource
DEFINE_EXCEPTION_OBJECT(resource_closed_exception, resource_exception,
    "Resource is no longer available. It may have been unmounted.");

DEFINE_EXCEPTION_OBJECT(resource_type_exception, resource_exception,
    "Unknown resource encoding or actual type does not match expected resource type.");

// resource_provider
DEFINE_EXCEPTION_OBJECT(resource_provider_exception, resource_exception,
    "Generic Resource Provider exception.");

// resourcefile_provider
DEFINE_EXCEPTION_OBJECT(resourcefile_provider_exception, resource_provider_exception,
    "Generic ResourceFile Provider exception.");

DEFINE_EXCEPTION_OBJECT(resourcefile_provider_not_implemented_exception, resourcefile_provider_exception,
    "Generic ResourceFile Provider not implemented exception.");

// filesystem_provider
DEFINE_EXCEPTION_OBJECT(filesystem_provider_exception, resource_provider_exception,
    "Generic Filesystem Provider exception.");

DEFINE_EXCEPTION_OBJECT(filesystem_provider_list_exception, filesystem_provider_exception,
    "Filesystem Provider list exception. Can not list given path.");

DEFINE_EXCEPTION_OBJECT(filesystem_provider_read_exception, filesystem_provider_exception,
    "Filesystem Provider read exception. Can not read given path. Path does not exist or is unreadable.");

DEFINE_EXCEPTION_OBJECT(filesystem_provider_type_exception, filesystem_provider_exception,
    "Filesystem Provider type exception. Can not figure out the type of the resource. File has no extension.");

// codec_manager
DEFINE_EXCEPTION_OBJECT(codec_manager_exception, resource_exception,
    "Generic Codec Manager exception.");

DEFINE_EXCEPTION_OBJECT(codec_manager_unknown_codec_exception, codec_manager_exception,
    "Unknown or unsupported codec requested from codec manager.");

DEFINE_EXCEPTION_OBJECT(codec_manager_codec_mismatch_exception, codec_manager_exception,
    "Resource encoding does not match expected resource type.");

// codec
DEFINE_EXCEPTION_OBJECT(codec_exception, codec_manager_exception,
    "Generic Codec exception.");

DEFINE_EXCEPTION_OBJECT(codec_decode_exception, codec_exception,
    "Error while decoding resource.");

// image_codec
DEFINE_EXCEPTION_OBJECT(image_codec_decode_exception, codec_decode_exception,
    "Error while decoding resource.");

// image_codec_png
DEFINE_EXCEPTION_OBJECT(codec_png_decode_exception, codec_decode_exception,
    "Error while decoding PNG image resource.");

// image
DEFINE_EXCEPTION_OBJECT(image_exception, resource_exception,
    "Image resource exception.");

DEFINE_EXCEPTION_OBJECT(image_data_exception, image_exception,
    "Image resource data exception.");

} // namespace resources
} // namespace aeon
