project(Game)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/engine/include)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../external/glad/include)

set(GAME_SOURCES
        src/Main.cpp
        src/Game/GameLogic.cpp)
set(GAME_HEADERS
        include/Game/GameLogic.h)

set(GLAD_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/../external/glad/src/glad.c)

add_executable(game ${GAME_SOURCES} ${GAME_HEADERS} ${GLAD_SOURCE})

target_link_libraries(game engine)
# target_include_directories(game PRIVATE ${CMAKE_BINARY_DIR}/assets)