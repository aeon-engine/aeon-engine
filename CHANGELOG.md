Aeon Game Engine
==============

Changelog
--------------

### Version 0.2

#### Features
  - Added support for 3D games.
  - Implemented (3D) mesh loading through the open asset import library.
  - Added platform and gfx handlers for GLES 2 and Raspberry Pi. (Highly experimental, see known issues).
  - Added experimental support for Qt as a platform.
  - Made materials more universal by changing the "shader" entry to a more specific "shader_gl3" and "shader_gles2".
  - Added debug option for OpenGL error checking and tracing.
  - Added OpenGL error checking.
  - Added get_framebuffer_size method for render targets.
  - Added initial experimental code for resource files.
  - Removed the need to start all resource paths with '/'. It is now added to the path automaticly if it's not there.
  - Added support for scaling to a scene node.
  - Added exception definitions for platform file io.
  - Added support for loading a config file.
  - Added support for setting and getting a mouse cursor mode. This allows for capturing the mouse cursor.
  - Replaced existing matrix rotation code in scene_node with a better implementation using transform-aware quaternion rotations.
  - Added material as a data object and refactored the material code path to be data driven in the future.
  - Atlasses are now UV based instead of pixel based for simplicity.
  - Made viewport coordinates relative between 0.0f and 1.0f to make window resizing a lot easier.
  - Implemented viewport zorder sorting and cleaned up the viewport code.
  - Enabled scissor testing for viewports.
  - Implemented get size from Atlas Region.
  - Add overload for sprite that takes the sprite size out of the given atlas region.
  - Allowed for setting the log level on the engine logger directly.
  - Added support for Axis Aligned bounding boxes to sprites.
  - Added Absolute Set Rotation & Set Position (and get) methods on scene nodes.

#### Bug fixes
  - Fixed multiple viewports and overlapping by applying glscissor when setting the viewport and clearing the z buffer right before rendering it.
  - Fixed backface culling in opengl.
  - Fixed rotation values in the examples that were broken due to the switch from radians to degrees. (Thanks Joe da Silva)
  - Fixed zlib submodule install target trying to install to Program Files by default.
  - Removed glEnable(GL_TEXTURE_2D) as this is not a valid call in OpenGL 3.3.
  - Report and squash OpenGL errors that come as a result of glewInit.
  - Fixed OpenGL profile not being set correctly to 3.3 forward compatible on OSX for the Qt platform.
  - Fixed header capitalization issue on linux with glew.h in the qt platform interface.
  - Fixed recursive filesystem issue with symbolic links in CMake that caused build failures in CLion.
  - Fixed bootstrap_pi.sh to actually work on a raspberry pi 3.
  - Raspberry pi: Disabled building of the IFC importer in the asset import library since the neon code appears broken on the Pi.
  - Fixed element count being incorrect in gfx_gl_mesh.
  - Fixed an issue where a VAO would be recreated every frame in gfx_gl_mesh.
  - Fixed object caching not garbage collecting any objects which could result in a nullpointer dereference.
  - Fixed matrix conversion in the assimp mesh codec resulting in an incorrect matrix being returned.
  - Added window settings so that more in-depth settings can be passed on to the platform for window creation.
  - Added support for single/double buffering and multisampling.
  - Fixed multiple viewports being broken.
  - Fixed example 3 crashing due to invalid animation sequence.
  - Fixed boken camera behaviour in 3d.

#### Infra
  - Add support for Visual Studio 2017 (RC).
  - Applied clang formatting.
  - Fixed tab usage in CMakeLists.txt.
  - Fixed cmake script for install deployment targets.
  - Added experimental deployment script.
  - Changed CI build system from make to xcodebuild.
  - Fixed windows build reporting green when something actually fails.
  - Added messages for each submodule so it's easier to see which submodule is outputing which message.
  - Added bootstrap for Windows 32-bit.
  - Fixed build failure on Visual Studio 2015 32-bit due to various warnings.
  - Added Open Assert Import Library as submodule.
  - Added CMake option to skip copying asset files to the runtime path.
  - Added CMake option to disable iterator debugging on Visual Studio.
  - Fixed windows CI build script to first delete the vs_build folder if it exists.
  - Fixed buildscripts to allow for git fetch instead of a git pull based CI build.
  - Added initial support for generating doxygen documentation.
  - Added clang format config file and script to run it recursively on the engine.
  - Disabled sorting include files in the clang format script to prevent newer versions from changing the header include order.
  - Added script to generate a dependency graph using cmake and graphviz (sfdp).
  - Speed up windows build significantly by introducing the /MP flag by default.
  - Fixed an issue where cmake would recursively copy headers that it installed by itself, causing major filesystem recursion issues.
  - Deploy the examples and their resources during install.
  - Added "_d" postfix for libraries build in debug mode.
  - Added deployment script for windows and added FindAeonEngine.cmake to the install target.
  - Added preliminairy support for the Clang compiler toolset in Visual Studio.
  - Added initial cpp check project file.

#### Other
  - Added incremental deploy script so that the whole engine doesn't need rebuilding for small changes.
  - Various refactors and cleanups throughout the code.
  - Introduced asset manager to fix a circular dependency between gfx and resources.
  - Moved initialization of glew to the glfw platform code so that the opengl gfx module contains only opengl code.
  - Removed sprite_batch to make the engine more generic (2d and 3d code paths are now the same).
  - Added more doxygen comments to various classes and methods.
  - Split the atlas data into a seperate object to remove the dependency of gfx on resources in the future.
  - The material codec no longer needs to know about the resource manager.
  - Removed various circular dependencies between subsystems and split the subsystems up into seperate libraries.
  - Changed default window size to 1280x720.
  - Removed confusing "using" directives.
  - Made various things references instead of value/shared_ptr passing.
  - Generally modernized the codebase in various locations (auto, move semantics, const correctness).
  - Made sprite_animation_settings movable.
  - Rectangles are now left, top, right, bottom instead of X, Y, width, height.
  - Split off position/rotation related code from scene_node into movable_object.

#### Known issues
  - Input example game "broken" after behaviour change in scene nodes.
  - GLES 2 device broke after major refactor and needs fixing

### Version 0.1
  - Initial alpha release of the Aeon Engine that supports only 2D games.

