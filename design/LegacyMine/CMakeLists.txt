cmake_minimum_required(VERSION 3.0.0)
project(minesweeper VERSION 0.1.0)

set(SFML_DIR "/usr/local/vcpkg/ports/sfml/SFML")
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

#Could not get the seperate directories to work
#include_directories(include)

file(GLOB SOURCES "src/*.cpp")
add_executable(minesweeper ${SOURCES})
target_link_libraries(minesweeper sfml-network sfml-audio sfml-graphics sfml-window sfml-system)


#add_library(Toolbox src/gamestate.cpp src/tile.cpp, src/toolbox.cpp)
#target_link_libraries(Toolbox sfml-graphics sfml-audio)

#add_executable(minesweeper src/minesweeper.cpp) 
#target_link_libraries(minesweeper sfml-graphics sfml-audio)
#target_link_libraries(minesweeper ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
