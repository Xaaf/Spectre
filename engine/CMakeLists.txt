project(Engine)

find_package(OpenGL REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../external/glad/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../external/glfw/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../external/glm)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../external/stb/include)


set(GLFW_BUILD_DOCS OFF CACHE BOOL "GLFW Lib Only")
set(GLFW_INSTALL OFF CACHE BOOL "GLFW Lib Only")

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../external/glfw ${CMAKE_CURRENT_BINARY_DIR}/build/glfw)

set(ENGINE_SOURCES
        src/Spectre/Engine.cpp
        src/Spectre/Input/Keyboard.cpp
        src/Spectre/Input/Mouse.cpp
        src/Spectre/Rendering/Renderer.cpp
        src/Spectre/Rendering/Window.cpp
        src/Spectre/Rendering/Arch/OpenGL/OpenGLMesh.cpp
        src/Spectre/Rendering/Arch/OpenGL/OpenGLRenderer.cpp
        src/Spectre/Rendering/Arch/OpenGL/OpenGLShader.cpp
        src/Spectre/Rendering/Arch/OpenGL/OpenGLTexture.cpp)
set(ENGINE_HEADERS
        include/Spectre/Engine.h
        include/Spectre/Input/InputCodes.h
        include/Spectre/Input/Keyboard.h
        include/Spectre/Input/Mouse.h
        include/Spectre/Rendering/MeshInterface.h
        include/Spectre/Rendering/Renderer.h
        include/Spectre/Rendering/RendererInterface.h
        include/Spectre/Rendering/ShaderInterface.h
        include/Spectre/Rendering/TextureInterface.h
        include/Spectre/Rendering/Vertex.h
        include/Spectre/Rendering/Window.h
        include/Spectre/Rendering/Arch/OpenGL/OpenGLMesh.h
        include/Spectre/Rendering/Arch/OpenGL/OpenGLRenderer.h
        include/Spectre/Rendering/Arch/OpenGL/OpenGLShader.h
        include/Spectre/Rendering/Arch/OpenGL/OpenGLTexture.h
        include/Spectre/System/Logging/Colours.h
        include/Spectre/System/Logging/Log.h
        include/Spectre/System/Logging/LogLevels.h)

set(GLAD_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/../external/glad/src/glad.c)

set(PCH_HEADER ${CMAKE_CURRENT_SOURCE_DIR}/include/sppch.h)
set(PCH_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/src/sppch.cpp)

add_library(pch STATIC ${PCH_SOURCE})
target_compile_features(pch PUBLIC cxx_std_17)
target_precompile_headers(pch PUBLIC ${PCH_HEADER})

add_library(engine STATIC ${ENGINE_SOURCES} ${ENGINE_HEADERS} ${GLAD_SOURCE})
target_link_libraries(engine ${OPENGL_LIBRARIES} glfw)