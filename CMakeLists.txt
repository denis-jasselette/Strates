cmake_minimum_required(VERSION 3.23)

project(Strates)
include(CheckIncludeFiles)

find_package(SFML 2.5.1 COMPONENTS system window graphics network REQUIRED)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
endif()

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/res DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_library(Json
  src/JSON/JSON.cpp
  src/JSON/JSONValue.cpp
)

add_library(Core
  src/application.cpp
  src/fow.cpp
  src/techTree.cpp
  src/building.cpp
  src/game.cpp
  src/map.cpp
  src/tileMap.cpp
  src/config.cpp
  src/gameScreen.cpp
  src/menuScreen.cpp
  src/unit.cpp
  src/cursor.cpp
  src/hud.cpp
  src/mouseEvent.cpp
  src/utils.cpp
  src/entity.cpp
  src/hudPanel.cpp
  src/player.cpp
  src/widget.cpp
  src/event.cpp
  src/imageManager.cpp
  src/screen.cpp
  src/ai.cpp
  src/action.cpp
  src/actionWait.cpp
  src/actionQueue.cpp
  src/actionMove.cpp
  src/playerColor.cpp
  src/spriteManager.cpp
)

add_executable(strates
  src/main.cpp
)

TARGET_LINK_LIBRARIES(strates Core Json sfml-window sfml-graphics sfml-system)

# Generate the Doxygen documentation if Doxygen is present
find_package(Doxygen)
if (DOXYGEN_FOUND)
  configure_file(
    ${CMAKE_SOURCE_DIR}/Doxyfile
    ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
    @ONLY)
  add_custom_target(doc
    ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Generating API documentation with Doxygen" VERBATIM
    )
else()
  message("Doxygen not found. The documentation will not be built.")
endif()
