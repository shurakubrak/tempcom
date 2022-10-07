cmake_minimum_required(VERSION 3.0.0)
project(AppSample VERSION 0.1.0)

include_directories("includes")
include_directories("source")

include(CTest)
enable_testing()

add_executable(AppSample main.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
