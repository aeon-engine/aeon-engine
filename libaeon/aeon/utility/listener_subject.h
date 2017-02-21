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
 * Base class for the subject of a observer pattern (listener class).
 * Observers are not specificly implemented since the pattern states that
 * only "Update()" is allowed. We want to be a little bit more generic,
 * hence the template.
 *
 * It's up to the implemented class to iterate over the listeners_ vector
 * and call the appropriate methods.
 */
template <typename T>
class listener_subject
{
public:
    /*!
     * Constructor
     */
    listener_subject() = default;

    /*!
     * Destructor
     */
    virtual ~listener_subject() = default;

    /*!
     * Attach a listener/observer to this subject.
     *
     * This does not take ownership of this pointer, so it's up to
     * the caller to keep this pointer alive, and delete it appropriately.
     */
    void attach_listener(T *listener)
    {
        listeners_.push_back(listener);
    }

    /*!
     * Remove a listener/observer from this subject. If this pointer was not previously attached, nothing happens.
     *
     * This will not delete the object, but merely detach it.
     */
    void detach_listener(T *listener)
    {
        listeners_.erase(std::remove(listeners_.begin(), listeners_.end(), listener), listeners_.end());
    }

    /*!
     * Detach all attached listeners.
     *
     * This will not delete the objects, but merely detach them.
     */
    void detach_all_listeners()
    {
        listeners_.clear();
    }

protected:
    std::vector<T *> listeners_;
};

} // namespace utility
} // namespace aeon
