cmake_minimum_required(VERSION 3.10)
project(Spectre)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(engine)
add_subdirectory(game)

# Add assets folder
file(GLOB SHADER_FILES "${CMAKE_SOURCE_DIR}/assets/shaders/*")
foreach(SHADER_FILE ${SHADER_FILES})
    get_filename_component(FILENAME ${SHADER_FILE} NAME)
    configure_file(${SHADER_FILE} ${CMAKE_BINARY_DIR}/game/assets/shaders/${FILENAME} COPYONLY)
endforeach()
file(GLOB TEXTURE_FILES "${CMAKE_SOURCE_DIR}/assets/textures/*")
foreach(TEXTURE_FILE ${TEXTURE_FILES})
    get_filename_component(FILENAME ${TEXTURE_FILE} NAME)
    configure_file(${TEXTURE_FILE} ${CMAKE_BINARY_DIR}/game/assets/textures/${FILENAME} COPYONLY)
endforeach()

# Add Doxygen support
find_package(Doxygen)

if (DOXYGEN_FOUND)
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)

    add_custom_target(doc_doxygen
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM)
else()
    message(WARNING "Doxygen not found, not building documentation")
endif()