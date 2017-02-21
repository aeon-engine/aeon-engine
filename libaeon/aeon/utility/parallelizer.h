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

class parallelizer : noncopyable
{
public:
    using task = std::function<void()>;
    using task_vector = std::vector<task>;

    parallelizer()
        : dispatcher_(dispatcher_stop_mode::stop_on_empty_queue)
    {
    }

    explicit parallelizer(const task_vector &tasks)
        : dispatcher_(dispatcher_stop_mode::stop_on_empty_queue)
    {
        add_jobs(tasks);
    }

    ~parallelizer() = default;

    void add_job(const task &task)
    {
        dispatcher_.post(task);
    }

    void add_jobs(const task_vector &tasks)
    {
        for (auto &task : tasks)
        {
            dispatcher_.post(task);
        }
    }

    void run(const int concurrency)
    {
        std::vector<std::thread> threads;
        for (int i = 0; i < concurrency; ++i)
        {
            threads.emplace_back(std::thread([this]() { dispatcher_.run(); }));
        }

        for (auto &thread : threads)
        {
            thread.join();
        }
    }

private:
    dispatcher dispatcher_;
};

} // namespace utility
} // namespace aeon
