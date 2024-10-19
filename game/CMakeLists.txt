project(Game)

set(GAME_SOURCES
        src/Main.cpp
        src/Game/GameLogic.cpp
)

set(GAME_HEADERS
        include/Game/GameLogic.h
)

# Create game executable
add_executable(game ${GAME_SOURCES} ${GAME_HEADERS} ${GLAD_SOURCE})

# Link the game to the engine library
target_link_libraries(game engine)

# Add includes for the game
target_include_directories(game PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/engine/include
        ${CMAKE_CURRENT_SOURCE_DIR}/../external/glad/include
        ${CMAKE_CURRENT_SOURCE_DIR}/../external/glm
)