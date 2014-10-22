#ifndef stdafx_h__
#define stdafx_h__

#include "buildconfig.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include <cstdint>
#include <list>
#include <string>
#include <sstream>
#include <iomanip>
#include <vector>
#include <map>
#include <queue>
#include <thread>
#include <mutex>
#include <set>
#include <memory>
#include <atomic>

#define GLEW_STATIC
#include <GL/glew.h>

#ifdef __APPLE__
#  include <OpenGL/gl.h>
#else
#  include <GL/gl.h>
#endif

#ifdef AEON_USE_GLFW_PLATFORM
#  include <GLFW/glfw3.h>
#endif

#ifdef AEON_USE_PNG
#  include <png.h>
#endif

#define AEON_UNUSED(x) (void)(x)

#include "console.h"
#include "consolelistener.h"
#include "framelistener.h"
#include "singleton.h"
#include "stringutils.h"
#include "buffer.h"
#include "timer.h"

#include "baseplatform.h"

#ifdef AEON_USE_GLFW_PLATFORM
#  include <GLFW/glfw3.h>
#  include "glfwplatform.h"
#endif

#include "stream.h"
#include "filestream.h"
#include "iostream.h"
#include "memorystream.h"
#include "configfile.h"
#include "streamlistener.h"
#include "image.h"
#include "imagecodec.h"
#include "imagecodecmanager.h"

#ifdef AEON_USE_PNG
#  include "imagecodecpng.h"
#endif

#include "resource.h"
#include "texture.h"
#include "shader.h"
#include "resourcemanager.h"
#include "texturemanager.h"
#include "shadermanager.h"

#include "gamestate.h"
#include "game.h"

#include "root.h"

#endif /* stdafx_h__ */
