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

#include <GL/glew.h>
#include <GL/gl.h>

#ifdef AEON_USE_GLFW_PLATFORM
#  include <GLFW/glfw3.h>
#endif

#define AEON_UNUSED(x) (void)(x)

#include "aeon/console/console.h"
#include "aeon/console/consolelistener.h"
#include "aeon/buildconfig.h"
#include "aeon/framelistener.h"
#include "aeon/utility/singleton.h"
#include "aeon/utility/stringutils.h"
#include "aeon/utility/buffer.h"
#include "aeon/utility/timer.h"

#include "aeon/platforms/baseplatform.h"

#ifdef AEON_USE_GLFW_PLATFORM
#  include <GLFW/glfw3.h>
#  include "aeon/platforms/glfwplatform.h"
#endif

#include "aeon/streams/stream.h"
#include "aeon/streams/filestream.h"
#include "aeon/streams/iostream.h"
#include "aeon/streams/memorystream.h"
#include "aeon/configfile.h"
#include "aeon/console/streamlistener.h"
#include "aeon/resources/image.h"
#include "aeon/resources/imagecodec.h"
#include "aeon/resources/imagecodecmanager.h"

#ifdef AEON_USE_PNG
#  include "aeon/resources/imagecodecpng.h"
#endif

#include "aeon/resources/resource.h"
#include "aeon/resources/texture.h"
#include "aeon/resources/shader.h"
#include "aeon/resources/resourcemanager.h"
#include "aeon/resources/texturemanager.h"
#include "aeon/resources/shadermanager.h"

#include "aeon/gamestate.h"
#include "aeon/game.h"


#include "aeon/root.h"
