project(Engine)

find_package(OpenGL REQUIRED)

# External dependencies
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../external/glfw ${CMAKE_CURRENT_BINARY_DIR}/build/glfw)

set(ENGINE_SOURCES
        src/Spectre/Engine.cpp
        src/Spectre/Input/Keyboard.cpp
        src/Spectre/Input/Mouse.cpp
        src/Spectre/Rendering/Model.cpp
        src/Spectre/Rendering/Renderer.cpp
        src/Spectre/Rendering/Window.cpp
        src/Spectre/Rendering/Arch/OpenGL/OpenGLMesh.cpp
        src/Spectre/Rendering/Arch/OpenGL/OpenGLRenderer.cpp
        src/Spectre/Rendering/Arch/OpenGL/OpenGLShader.cpp
        src/Spectre/Rendering/Arch/OpenGL/OpenGLTexture.cpp
)

set(ENGINE_HEADERS
        include/Spectre/Engine.h
        include/Spectre/Input/InputCodes.h
        include/Spectre/Input/Keyboard.h
        include/Spectre/Input/Mouse.h
        include/Spectre/Rendering/MeshBase.h
        include/Spectre/Rendering/Model.h
        include/Spectre/Rendering/Renderer.h
        include/Spectre/Rendering/RendererBase.h
        include/Spectre/Rendering/ShaderBase.h
        include/Spectre/Rendering/TextureBase.h
        include/Spectre/Rendering/Vertex.h
        include/Spectre/Rendering/Window.h
        include/Spectre/Rendering/Arch/OpenGL/OpenGLMesh.h
        include/Spectre/Rendering/Arch/OpenGL/OpenGLRenderer.h
        include/Spectre/Rendering/Arch/OpenGL/OpenGLShader.h
        include/Spectre/Rendering/Arch/OpenGL/OpenGLTexture.h
        include/Spectre/System/Logging/Colours.h
        include/Spectre/System/Logging/Log.h
        include/Spectre/System/Logging/LogLevels.h
)

# GLAD source
set(GLAD_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/../external/glad/src/glad.c)

# PCH setup
set(PCH_HEADER ${CMAKE_CURRENT_SOURCE_DIR}/include/sppch.h)
set(PCH_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/src/sppch.cpp)

# Create PCH target
add_library(pch STATIC ${PCH_SOURCE})

# Make sure PCH has access to the necessary includes
target_include_directories(pch PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../external/glad/include
        ${CMAKE_CURRENT_SOURCE_DIR}/../external/glfw/include
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(pch PUBLIC cxx_std_17)
target_precompile_headers(pch PUBLIC ${PCH_HEADER})

# Create engine library
add_library(engine STATIC ${ENGINE_SOURCES} ${ENGINE_HEADERS} ${GLAD_SOURCE})

# Link libraries and include directories for the engine
target_link_libraries(engine PRIVATE ${OPENGL_LIBRARIES} glfw)
target_include_directories(engine PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../external/glad/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../external/glfw/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../external/glm
    ${CMAKE_CURRENT_SOURCE_DIR}/../external/stb/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)