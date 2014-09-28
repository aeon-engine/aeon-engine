#set(common_HEADERS ${GLFW_BINARY_DIR}/src/glfw_config.h internal.h
#                   ${GLFW_SOURCE_DIR}/include/GLFW/glfw3.h
#                   ${GLFW_SOURCE_DIR}/include/GLFW/glfw3native.h)

include_directories(${AEON_SOURCE_DIR}/include)
link_directories(${AEON_BINARY_DIR}/src)

set(common_SOURCES
	root.cpp
	game.cpp
	configfile.cpp
	console/console.cpp
	console/streamlistener.cpp
	resources/image.cpp
	resources/imagecodecmanager.cpp
	resources/imagecodecpng.cpp
	resources/resource.cpp
	resources/resourcemanager.cpp
	resources/shader.cpp
	resources/shadermanager.cpp
	resources/texture.cpp
	resources/texturemanager.cpp
	streams/filestream.cpp
	streams/iostream.cpp
	streams/memorystream.cpp
	streams/stream.cpp
	utility/buffer.cpp
	utility/stringutils.cpp
	utility/timer.cpp
)

if(GLFW3_FOUND)
	message(STATUS "Compiling with GLFW Application")
	set(optional_SOURCES platforms/glfwplatform.cpp)

endif(GLFW3_FOUND)

add_library(aeon3d ${common_SOURCES} ${optional_SOURCES})
