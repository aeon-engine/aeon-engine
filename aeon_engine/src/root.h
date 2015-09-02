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

#ifndef root_h__
#define root_h__

namespace aeon
{

typedef std::list<framelistener *> framelisteners;

/*!
 * \brief The one class
 *
 * This class is the heart of the Aeon Engine. It handles:
 * - Initialization
 * - Setting up the selected platform
 * - Main loop
 * - Cleaning up on shutdown
 */
class root : public aeon::utility::singleton<root>
{
public:
    /*!
     * Destructor
     */
    virtual ~root();

    /*!
     * Initialize the engine. This function will create a singleton instance of
     * this Root class and initialize the given platform.
     * \param platform An instance of a platform implementation 
     *                 (for example GLFW)
     * \return True if successfully initialized. False on any error. The cause
     *         of the failure is logged to the console.
     */
    static bool initialize(platforms::base_platform_ptr platform);

    /*!
     * Start the engine's main loop. This function can only be called after
     * initialize was called and returned true. This is a blocking call and 
     * will run until stop() is called.
     */
    void run();
    
    /*!
     * Start the engine's main loop. This function can only be called after
     * initialize was called and returned true. This is a blocking call and 
     * will run until stop() is called.
     */
    void stop();

    /*!
     * Add a framelistener event handler to the main loop. Adding an instance
     * of a framelistener here will cause that listener to receive events every
     * frame and render update.
     * \param listener An instance of a framelistener.
     */
    void add_frame_listener(framelistener *listener);
    
    /*!
     * Remove a framelistener event handler from the main loop. Removing an 
     * instance of a framelistener here will cause that listener to stop 
     * receiving events every frame and render update. The instance must have
     * previously been added.
     * \param listener An instance of a framelistener.
     */
    void remove_frame_listener(framelistener *listener);
    
    /*!
     * Remove all framelistener event handlers from the main loop. Removing an 
     * instance of a framelistener here will cause that listener to stop 
     * receiving events every frame and render update. The instance must have
     * previously been added.
     */
    void remove_all_frame_listeners();

protected:
    /*!
     * Constructor
     *
     * This class is instantiated in the static initialize function.
     *
     * \param platform An instance of a platform implementation 
     *                 (for example GLFW)
     */
    root(platforms::base_platform_ptr platform);

    /*!
     * Initialize the engine. This function will create a singleton instance of
     * this Root class and initialize the given platform. This is the actual
     * implementation of the initialize function and is called after root was
     * instantiated.
     * \param platform An instance of a platform implementation 
     *                 (for example GLFW)
     * \return True if successfully initialized. False on any error. The cause
     *         of the failure is logged to the console.
     */
    bool __initialize_impl(platforms::base_platform_ptr platform);

    /*!
     * True if the engine has been successfully initialized. False by default.
     */
    bool initialized_;
    
    /*!
     * True if the engine is running. The engine will stop when this variable 
     * is set to false. False by default.
     */
    bool running_;

    /*!
     * A list of all framelisteners that were added with add_frame_listener()
     */
    framelisteners frame_listeners_;
    
    /*!
     * An instance of the platform implementation.
     */
    platforms::base_platform_ptr platform_;
};

} // namespace aeon

#endif // root_h__
