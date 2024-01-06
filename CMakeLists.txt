cmake_minimum_required(VERSION 3.16.3)
project(Minesweeper VERSION 0.1.0 LANGUAGES C CXX)
enable_testing()

include(CTest)
include(InstallRequiredSystemLibraries)

file(GLOB SOURCES "src/*.cpp")                              #--> Fixed the linker problem?
# set(SFML_DIR "/usr/local/vcpkg/ports/sfml/SFML")          #--> Fixed the linker problem?
set(SFML_DIR "/mnt/c/Libraries/SFML-2.5.1/")                #--> Fixed the linker problem?
set(EXECUTABLE_NAME "minesweeper")
add_executable(${EXECUTABLE_NAME} src/main.cpp src/textureManager.cpp src/randomGen.cpp src/tile.cpp src/board.cpp )

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2.5 COMPONENTS graphics audio network window REQUIRED)
target_link_libraries(${EXECUTABLE_NAME} sfml-network sfml-audio sfml-graphics sfml-window sfml-system)
set(EXECUTABLE_OUTPUT_PATH ../)

set(CPACK_PACKAGE_VERSION_MINOR "${myproject_VERSION_MINOR}")
include(CPack)
