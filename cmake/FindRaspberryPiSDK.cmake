# Copyright (c) 2012-2017 Robin Degen
#
# Permission is hereby granted, free of charge, to any person
# obtaining a copy of this software and associated documentation
# files (the "Software"), to deal in the Software without
# restriction, including without limitation the rights to use,
# copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the
# Software is furnished to do so, subject to the following
# conditions:
#
# The above copyright notice and this permission notice shall be
# included in all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
# OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
# NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
# HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
# WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
# FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
# OTHER DEALINGS IN THE SOFTWARE.

message(STATUS "Running Find Raspberry Pi SDK.")

find_path(RASPBERRY_PI_INCLUDE_PATH "bcm_host.h"
    PATHS $ENV{RASPBERRY_PI_SDK_ROOT}/include
)

if (NOT RASPBERRY_PI_INCLUDE_PATH)
    message(FATAL "Could not find bcm_host.h. Please set the environment variable RASPBERRY_PI_SDK_ROOT.")
endif ()

set(RASPBERRY_PI_INCLUDE_PATHS ${RASPBERRY_PI_INCLUDE_PATH})
list(APPEND RASPBERRY_PI_INCLUDE_PATHS ${RASPBERRY_PI_INCLUDE_PATH}/interface/vcos/pthreads)
list(APPEND RASPBERRY_PI_INCLUDE_PATHS ${RASPBERRY_PI_INCLUDE_PATH}/interface/vmcs_host/linux)

set(RASPBERRY_PI_LIBRARIES "")
foreach(component ${RaspberryPiSDK_FIND_COMPONENTS})
    find_library(
        RASPBERRY_PI_COMPONENT_${component}_LIBRARIES NAMES ${component}
        PATHS $ENV{RASPBERRY_PI_SDK_ROOT}/lib
    )

    if (NOT RASPBERRY_PI_COMPONENT_${component}_LIBRARIES)
        message(FATAL_ERROR "Could not find Raspberry Pi component: ${component}.")
    endif ()

    set(_COMPONENT_PATH ${RASPBERRY_PI_COMPONENT_${component}_LIBRARIES})
    message(STATUS "  Found ${component}: ${_COMPONENT_PATH}")

    set(RASPBERRY_PI_LIBRARIES "${_COMPONENT_PATH};${RASPBERRY_PI_LIBRARIES}")
endforeach()

add_library(RaspberryPiSdk INTERFACE IMPORTED)

set_target_properties(RaspberryPiSdk PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${RASPBERRY_PI_INCLUDE_PATHS}"
    INTERFACE_LINK_LIBRARIES "${RASPBERRY_PI_LIBRARIES}"
)
