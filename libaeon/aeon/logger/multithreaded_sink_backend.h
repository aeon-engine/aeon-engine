/*
 * Copyright (c) 2012-2017 Robin Degen
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

namespace aeon
{
namespace logger
{

class multithreaded_sink_backend : public base_backend
{
private:
    struct log_message_queue_entry
    {
        std::string message;
        std::string module;
        log_level level;
    };

    typedef std::vector<log_message_queue_entry> log_message_queue;
    typedef std::set<log_sink *> sink_set;

public:
    multithreaded_sink_backend()
        : base_backend(log_level::message)
        , running_(true)
    {
        handle_background_thread_();
    }

    multithreaded_sink_backend(log_level level)
        : base_backend(level)
        , running_(true)
    {
        handle_background_thread_();
    }

    virtual ~multithreaded_sink_backend()
    {
        stop();
    }

    void add_sink(log_sink *sink)
    {
        std::lock_guard<std::mutex> lock(sink_mutex_);
        sinks_.insert(sink);
    }

    void remove_all_sinks()
    {
        std::lock_guard<std::mutex> lock(sink_mutex_);
        sinks_.clear();
    }

    void stop()
    {
        if (!running_)
            return;

        running_ = false;
        cv_.notify_one();
        thread_.join();
    }

private:
    void handle_background_thread_()
    {
        running_ = true;

        thread_ = std::thread([this]() {
            while (running_)
            {
                std::unique_lock<std::mutex> lock(signal_mutex_);
                cv_.wait(lock);

                if (!running_)
                    break;

                // Move the message queue into a new copy and empty the real queue
                queue_mutex_.lock();
                log_message_queue log_queue = std::move(log_queue_);
                log_queue_ = log_message_queue();
                queue_mutex_.unlock();

                bool reprocess_queue = true;

                while (reprocess_queue)
                {
                    // Copy the sinks
                    sink_mutex_.lock();
                    sink_set sinks = sinks_;
                    sink_mutex_.unlock();

                    // Handle all messages
                    for (auto &msg : log_queue)
                    {
                        for (auto &sink : sinks)
                        {
                            sink->log(msg.message, msg.module, msg.level);
                        }
                    }

                    queue_mutex_.lock();
                    if (!log_queue_.empty())
                    {
                        log_queue = std::move(log_queue_);
                        log_queue_ = log_message_queue();
                        reprocess_queue = true;
                    }
                    else
                    {
                        reprocess_queue = false;
                    }
                    queue_mutex_.unlock();
                }
            }
        });
    }

    void log(const std::string &message, const std::string &module, const log_level level) override
    {
        std::lock_guard<std::mutex> lock(queue_mutex_);
        log_queue_.push_back({message, module, level});
        cv_.notify_one();
    }

    std::thread thread_;
    std::mutex signal_mutex_;
    std::condition_variable cv_;

    std::mutex sink_mutex_;
    sink_set sinks_;

    std::mutex queue_mutex_;
    log_message_queue log_queue_;

    volatile bool running_;
};

} // namespace logger
} // namespace aeon
