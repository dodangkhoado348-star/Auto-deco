cmake_minimum_required(VERSION 3.19)
project(AutoDeco VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
    Geode
    GIT_REPOSITORY https://github.com/geode-sdk/geode.git
    GIT_TAG main
)
FetchContent_MakeAvailable(Geode)

# Khai báo file nguồn chính xác trong thư mục src/
setup_geode_mod(AutoDeco SOURCES src/main.cpp)
