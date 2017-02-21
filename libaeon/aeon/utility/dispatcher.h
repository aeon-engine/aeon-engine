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
namespace utility
{

/*!
 * Determines how the dispatcher should stop. Either by calling stop manually (manual_stop) or automaticly
 * when the queue is determined to be empty. Be sure all jobs are queued before calling run when using this mode to
 * prevent race conditions.
 */
enum dispatcher_stop_mode
{
    manual_stop,
    stop_on_empty_queue
};

class dispatcher : noncopyable
{
public:
    static const int signal_wait_timeout_ms = 100;

    dispatcher(dispatcher_stop_mode stop_mode = dispatcher_stop_mode::manual_stop)
        : running_(false)
        , stop_mode_(stop_mode)
    {
    }

    ~dispatcher() = default;

    void run_one()
    {
        std::function<void()> func;
        {
            std::unique_lock<std::mutex> lock(mutex_);
            signal_cv_.wait(lock, [this]() { return !queue_.empty() || !running_; });

            if (!queue_.empty())
            {
                func = queue_.front();
                queue_.pop();
            }

            if (stop_mode_ == dispatcher_stop_mode::stop_on_empty_queue)
            {
                if (queue_.empty())
                    running_ = false;
            }
        }

        if (func)
            func();
    }

    void run()
    {
        running_ = true;

        while (running_)
        {
            run_one();
        }
    }

    void post(std::function<void()> job)
    {
        std::unique_lock<std::mutex> lock(mutex_);
        queue_.push(job);
        signal_cv_.notify_one();
    }

    void call(std::function<void()> job)
    {
        std::promise<void> promise;
        std::future<void> future = promise.get_future();

        post([&job, &promise]() {
            try
            {
                job();
                promise.set_value();
            }
            catch (...)
            {
                promise.set_exception(std::current_exception());
            }
        });

        return future.get();
    }

    template <typename T, typename std::enable_if<!std::is_void<T>::value>::type * = nullptr>
    T call(std::function<T()> job)
    {
        std::promise<T> promise;
        std::future<T> future = promise.get_future();

        post([&job, &promise]() {
            try
            {
                promise.set_value(job());
            }
            catch (...)
            {
                promise.set_exception(std::current_exception());
            }
        });

        return future.get();
    }

    void stop()
    {
        std::lock_guard<std::mutex> guard(mutex_);
        running_ = false;
        signal_cv_.notify_all();
    }

    void reset()
    {
        std::lock_guard<std::mutex> guard(mutex_);
        queue_ = std::queue<std::function<void()>>();
    }

private:
    std::mutex mutex_;
    std::condition_variable signal_cv_;
    std::queue<std::function<void()>> queue_;
    bool running_;
    dispatcher_stop_mode stop_mode_;
};

} // namespace utility
} // namespace aeon
