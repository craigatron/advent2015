add_executable(day4 main.cpp)
find_package(OpenSSL REQUIRED)
target_link_libraries(day4 PRIVATE OpenSSL::SSL)