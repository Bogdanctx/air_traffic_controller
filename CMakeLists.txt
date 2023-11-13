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
)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/Users/bobot/Desktop/air_traffic_controller/libraries/SFML-2.6.1/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

include_directories(C:/Users/bobot/Desktop/air_traffic_controller/libraries/SFML-2.6.1/include)
target_link_libraries(air_traffic_controller sfml-system sfml-window sfml-graphics sfml-audio)