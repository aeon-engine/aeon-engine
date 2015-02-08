/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2014 Robin Degen
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

#include "stdafx.h"

namespace aeon
{

timer::timer()
{
    reset();
}

timer::~timer()
{

}

void timer::reset()
{
    start_time_ = std::chrono::system_clock::now();
}

double timer::get_time_difference()
{
    std::chrono::time_point<std::chrono::system_clock> now = 
        std::chrono::system_clock::now();
    
    std::chrono::duration<double> elapsed_seconds = now - start_time_;

    return elapsed_seconds.count();
}

} /* namespace aeon */
