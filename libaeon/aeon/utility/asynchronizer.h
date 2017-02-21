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

class asynchronizer : noncopyable
{
public:
    asynchronizer() = default;
    ~asynchronizer() = default;

    void post(std::function<void()> job)
    {
        std::unique_lock<std::mutex> lock(mutex_);
        queue_.push(job);
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

    void reset()
    {
        std::lock_guard<std::mutex> guard(mutex_);
        queue_ = std::queue<std::function<void()>>();
    }

protected:
    void execute_all()
    {
        while (execute_one())
        {
        }
    }

    bool execute_one()
    {
        std::function<void()> func;
        {
            std::lock_guard<std::mutex> guard(mutex_);

            if (queue_.empty())
                return false;

            func = queue_.front();
            queue_.pop();
        }

        func();
        return true;
    }

private:
    std::mutex mutex_;
    std::queue<std::function<void()>> queue_;
};

} // namespace utility
} // namespace aeon
