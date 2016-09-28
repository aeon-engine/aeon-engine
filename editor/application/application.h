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

#include <aeon/utility.h>
#include <QtWidgets/QApplication>

namespace aeon
{
namespace editor
{

class application : utility::noncopyable
{
public:
    application(int argc, char *argv[]);
    ~application() = default;

    int exec() const;
private:
    void apply_stylesheet();

    QApplication qt_application_;
};

} // namespace editor
} // namespace aeon