cmake_minimum_required(VERSION 3.23)
project(example)

set(CMAKE_CXX_STANDARD 14)

set(VVLOG vvlog.cpp)

add_executable(${PROJECT_NAME}
        example.cpp
        ${VVLOG}
        )

include(FetchContent)
FetchContent_Declare(spdlog
        URL https://github.com/gabime/spdlog/archive/refs/tags/v1.10.0.tar.gz)
FetchContent_MakeAvailable(spdlog)

target_link_libraries(${PROJECT_NAME} PRIVATE spdlog)