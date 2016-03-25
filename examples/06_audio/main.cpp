/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2016 Robin Degen & Steven Hoving
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

#include "application.h"
#include <audio/audio.h>
#include <resources/resource_manager.h>

void play_sample(const char *filename)
{
    aeon::audio::device aldevice;
    aeon::audio::listener listener;
    aeon::audio::buffer_static_ptr buffer = std::make_shared<aeon::audio::buffer_static>();
    buffer->load(filename);

    aeon::audio::source_ptr source = aldevice.get_source();
    source->bind(buffer);
    source->play();

    // ugly... but just wait until we finsihed playing the audio sample
    while (source->get_status() == aeon::audio::source_status::playing)
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
}

void test_static()
{
    //play_sample(R"(D:\dev\aeon\audio\test\16_22050_stereo.wav)");
    //play_sample(R"(D:\dev\aeon\audio\test\16_22050_stereo.ogg)");
    //play_sample(R"(D:\dev\aeon\audio\test\16_44100_mono.wav)");
    play_sample(R"(D:\dev\aeon\audio\test\16_44100_mono.ogg)");
}

void play_stream(const char *filename)
{
    aeon::audio::device aldevice;
    aeon::audio::listener listener;

    aeon::audio::buffer_streaming_ptr buffer = std::make_shared<aeon::audio::buffer_streaming>();
    buffer->load(filename);

    aeon::audio::source_ptr source = aldevice.get_source();
    source->bind(buffer);
    source->play();

    while (source->get_status() == aeon::audio::source_status::playing)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void test_dynamic()
{
    play_stream(R"(D:\dev\aeon\audio\test\16_22050_stereo.ogg)");
    play_stream(R"(D:\dev\aeon\audio\test\16_44100_mono.ogg)");
    //play_stream(R"(D:\dev\aeon\audio\test\stream\16_44100_stereo.ogg)");
}

void test_dynamic_pause()
{
    aeon::audio::device aldevice;
    aeon::audio::listener listener;

    aeon::audio::buffer_streaming_ptr buffer = std::make_shared<aeon::audio::buffer_streaming>();
    buffer->load(R"(D:\dev\aeon\audio\test\stream\16_44100_stereo.ogg)");

    aeon::audio::source_ptr source = aldevice.get_source();
    source->bind(buffer);
    source->play();

    std::this_thread::sleep_for(std::chrono::milliseconds(10000));

    source->pause();

    std::this_thread::sleep_for(std::chrono::milliseconds(2000));

    source->play();

    while (source->get_status() == aeon::audio::source_status::playing)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void test_dynamic_reuse()
{
    aeon::audio::device aldevice;
    aeon::audio::listener listener;
    aeon::audio::buffer_streaming_ptr buffer = std::make_shared<aeon::audio::buffer_streaming>();
    //buffer->load(R"(D:\dev\aeon\audio\test\16_22050_stereo.ogg)");
    buffer->load(R"(D:\dev\aeon\audio\test\stream\16_44100_stereo.ogg)");

    aeon::audio::source_ptr source = aldevice.get_source();
    source->bind(buffer);
    source->play();

    while (source->get_status() == aeon::audio::source_status::playing)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    source->play();

    while (source->get_status() == aeon::audio::source_status::playing)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

int main(int argc, char *argv[])
{
    application app;
    app.main(argc, argv);

// disabled, old & classic audio engine api
#if 0
    test_static();
    test_dynamic();
    //test_dynamic_pause();
    test_dynamic_reuse();

    system("pause");
#endif
    return 0;
}
