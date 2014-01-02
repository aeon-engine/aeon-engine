#set(common_HEADERS ${GLFW_BINARY_DIR}/src/glfw_config.h internal.h
#                   ${GLFW_SOURCE_DIR}/include/GLFW/glfw3.h
#                   ${GLFW_SOURCE_DIR}/include/GLFW/glfw3native.h)

include_directories(${AEON_SOURCE_DIR}/include)
link_directories(${AEON_BINARY_DIR}/src)

set(common_SOURCES AeonBaseApplication.cpp AeonImage.cpp AeonBuffer.cpp AeonIOStream.cpp
AeonConfigFile.cpp AeonMemoryStream.cpp AeonConsole.cpp AeonResource.cpp AeonConsoleStreamListener.cpp 
AeonResourceManager.cpp AeonFileStream.cpp AeonStream.cpp AeonGame.cpp AeonStringUtils.cpp 
AeonTexture.cpp AeonImageCodecManager.cpp AeonTextureManager.cpp AeonImageCodecPNG.cpp)

if(GLFW3_FOUND)
	message(STATUS "Compiling with GLFW Application")
	set(optional_SOURCES AeonGLFWApplication.cpp)

endif(GLFW3_FOUND)

add_library(aeon3d ${common_SOURCES} ${optional_SOURCES})
