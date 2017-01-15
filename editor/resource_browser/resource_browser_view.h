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

#include <QtWidgets/QDialog>
#include <memory>

namespace Ui
{
    class frm_resource_editor_view;
}

namespace aeon
{
namespace editor
{

class resource_browser_view : public QDialog
{
Q_OBJECT

public:
    resource_browser_view(QWidget *parent = nullptr);
    ~resource_browser_view() override;

private:
    std::unique_ptr<Ui::frm_resource_editor_view> ui_;
};

} // namespace editor
} // namespace aeon
