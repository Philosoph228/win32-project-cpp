cmake_minimum_required(VERSION 3.18 FATAL_ERROR)

project(win32app)

add_executable(${PROJECT_NAME} WIN32 main.cpp)
target_compile_definitions(${PROJECT_NAME} PRIVATE _UNICODE UNICODE)
target_link_options(${PROJECT_NAME} PRIVATE -municode)

