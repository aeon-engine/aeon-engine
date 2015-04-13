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

#ifndef stdafx_h__
#define stdafx_h__

#include "buildconfig.h"

/************************************************************************/
/* Common headers                                                       */
/************************************************************************/

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
#include <array>

/************************************************************************/
/* External libraries                                                   */
/************************************************************************/
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

#ifdef AEON_USE_GLFW_PLATFORM
#  include <GLFW/glfw3.h>
#endif

#ifdef AEON_USE_ASSIMP
#  include <assimp/Importer.hpp>
#  include <assimp/scene.h>
#  include <assimp/postprocess.h>
#endif

#include <glm/glm.hpp>
#include <aeon/utility.h>

/************************************************************************/
/* Engine                                                               */
/************************************************************************/
#define AEON_UNUSED(x) (void)(x)

#include "console.h"
#include "consolelistener.h"
#include "framelistener.h"
#include "stringutils.h"
#include "buffer.h"
#include "baseplatform.h"

#ifdef AEON_USE_GLFW_PLATFORM
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

#include "scene.h"
#include "scenecodec.h"
#include "scenecodecmanager.h"

#ifdef AEON_USE_ASSIMP
#  include "scenecodecassimp.h"
#endif

#include "resource.h"
#include "texture.h"
#include "shader.h"
#include "material.h"
#include "mesh.h"

#include "resourcemanager.h"
#include "texturemanager.h"
#include "shadermanager.h"
#include "materialmanager.h"
#include "meshmanager.h"

#include "gamestate.h"
#include "game.h"

#include "root.h"

/************************************************************************/
/* Game implementation                                                  */
/************************************************************************/
#include "application.h"
#include "rpggame.h"
#include "gamestate_game.h"

#endif /* stdafx_h__ */
