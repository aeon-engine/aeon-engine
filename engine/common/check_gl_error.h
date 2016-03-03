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

#ifdef AEON_ENABLE_GL_ERROR_CHECKS
#define AEON_CHECK_GL_ERROR() aeon::common::check_gl_error(__FILE__, __LINE__);
#else
#define AEON_CHECK_GL_ERROR() do{} while(0)
#endif

namespace aeon
{
namespace common
{

#ifdef AEON_ENABLE_GL_ERROR_CHECKS
void check_gl_error(const char *file, int line);
#endif

} // namespace common
} // namespace aeon