cmake_minimum_required(VERSION 3.8.0)
project(http_server VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_subdirectory(source)

set_property(TARGET http_server PROPERTY CMAKE_CXX_STANDARD 20)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
