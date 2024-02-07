add_executable(http_server main.cpp Log.cpp Helpers.cpp Server.cpp)
include_directories(${http_server_SOURCE_DIR}/headers)
target_link_libraries(http_server PRIVATE Threads::Threads)