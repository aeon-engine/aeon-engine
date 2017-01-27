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

#include <resource_browser/resource_browser_view.h>
#include <ui_resource_browser.h>

#include <aeon/platform/generic/platform_generic_filesystem_interface.h>
#include <aeon/platform/platform_interface.h>
#include <aeon/resources/resource_manager.h>
#include <aeon/resources/providers/filesystem_provider.h>

namespace aeon
{
namespace editor
{

resource_browser_view::resource_browser_view(QWidget *parent)
    : QDialog(parent)
    , ui_(std::make_unique<Ui::frm_resource_editor_view>())
{
    ui_->setupUi(this);

    platform::platform_interface pint(std::make_unique<platform::generic::platform_filesystem_interface>());
    resources::resource_manager mgr(pint);

    mgr.mount(std::make_shared<aeon::resources::filesystem_provider>("."), "/");

    {
        auto ship = mgr.load_resource_wrapper<resources::image_resource_wrapper>("resources/textures/ships.png");
        auto ship_img = ship->open();
        auto &ship_img_data = ship_img->get_data();
        QImage image(ship_img_data.get_data().data(), ship_img_data.get_width(), ship_img_data.get_height(), QImage::Format_RGBA8888);
        ui_->listWidget->addItem(new QListWidgetItem(QIcon(QPixmap::fromImage(image)), "Ships.png"));
    }
    {
        auto ship = mgr.load_resource_wrapper<resources::image_resource_wrapper>("resources/textures/valheim.png");
        auto ship_img = ship->open();
        auto &ship_img_data = ship_img->get_data();
        QImage image(ship_img_data.get_data().data(), ship_img_data.get_width(), ship_img_data.get_height(), QImage::Format_RGBA8888);
        ui_->listWidget->addItem(new QListWidgetItem(QIcon(QPixmap::fromImage(image)), "valheim.png"));
    }
}

resource_browser_view::~resource_browser_view() = default;

} // namespace editor
} // namespace aeon
