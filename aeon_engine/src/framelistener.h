/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2014 Robin Degen
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

#ifndef framelistener_h__
#define framelistener_h__

namespace aeon
{

/*!
 * \brief Base class for framelisteners
 *
 * This class serves as the base class for all framelisteners. A class derived
 * from this can be added to Aeon::Root as a framelistener and will then start
 * receiving events.
 */
class framelistener
{
public:
    /*!
     * Constructor
     */
    framelistener() {}
    
    /*!
     * Destructor
     */
    ~framelistener() {}

    /*!
     * Called every frame update, before all render events.
     * \param dt The time difference in seconds between this frame and the 
     *           previous frame.
     * \return False if the engine should stop running after this frame.
     */
    virtual bool on_frame(float dt) = 0;
    
    /*!
     * Called every render update, after all frame events were handled.
     * \return False if the engine should stop running after this frame.
     */
    virtual bool on_render() = 0;
};

} /* namespace aeon */

#endif /* framelistener_h__ */
