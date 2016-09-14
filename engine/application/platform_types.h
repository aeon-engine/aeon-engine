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

#include <build_config.h>

#ifdef AEON_PLATFORM_GLFW
#include <platform/glfw/platform_glfw_interface.h>
using selected_platform_interface = aeon::platform::glfw::platform_interface;
#endif // AEON_PLATFORM_GLFW

#ifdef AEON_PLATFORM_RPI
#include <platform/rpi/platform_rpi_interface.h>
using selected_platform_interface = aeon::platform::rpi::platform_interface;
#endif // AEON_PLATFORM_RPI

#ifdef AEON_PLATFORM_QT
#include <platform/qt/platform_qt_interface.h>
using selected_platform_interface = aeon::platform::qt::platform_interface;
#endif // AEON_PLATFORM_QT

#ifdef AEON_PLATFORM_NULL
#include <platform/null/platform_null_interface.h>
using selected_platform_interface = aeon::platform::null::platform_interface;
#endif // AEON_PLATFORM_NULL
