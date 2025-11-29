cmake_minimum_required(VERSION 3.10)

project(Wrapper LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(app
    main.cpp
    tests.cpp
    wrapper.cpp
    engine.cpp
)