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

#ifndef application_h__
#define application_h__

namespace aeon
{

class application : public framelistener
{
public:
    application();
    ~application();

    void main(int argc, char *argv[]);

    bool on_frame(float dt);
    bool on_render();

private:
    void __setup_console();

    aeon::platforms::glfw *platform_;
};

} // namespace aeon

#endif // application_h__
