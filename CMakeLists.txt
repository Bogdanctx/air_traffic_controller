cmake_minimum_required(VERSION 3.26)
project(air_traffic_controller)

set(CMAKE_CXX_STANDARD 20)

add_executable(air_traffic_controller main.cpp
        Game.cpp
        Game.h
        Airplane.cpp
        Airplane.h
        Resources.cpp
        Resources.h
        Math.cpp
        Math.h
        enums.h
)

set(SFML_DIR, "/home/bgd/Desktop/air_traffic_controller/libraries/SFML-2.6.1/lib/cmake/SFML")

set(SFML_INCLUDE_DIR "/home/bgd/Desktop/air_traffic_controller/libraries/SFML-2.6.1/include")
set(SFML_LIBRARY_DIR "/home/bgd/Desktop/air_traffic_controller/libraries/SFML-2.6.1/lib")
link_directories("/home/bgd/Desktop/air_traffic_controller/libraries/SFML-2.6.1/lib")
include_directories("/home/bgd/Desktop/air_traffic_controller/libraries/SFML-2.6.1/include")
set(SFML_DIR "/home/bgd/Desktop/air_traffic_controller/libraries/SFML-2.6.1/lib/cmake/SFML")
find_package(SFML 2.6.1 COMPONENTS system window graphics network audio)

if(SFML_FOUND)
    message(STATUS "SFML_INCLUDE_DIRS: ${SFML_INCLUDE_DIR}")
    message(STATUS "SFML_LIBRARIES: ${SFML_LIBRARIES}")
    message(STATUS "SFML_VERSION: ${SFML_VERSION}")
    include_directories(${SFML_INCLUDE_DIRS})
endif()

target_link_libraries(air_traffic_controller sfml-graphics sfml-window sfml-graphics sfml-network sfml-audio)