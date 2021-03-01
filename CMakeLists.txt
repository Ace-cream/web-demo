# project setting
cmake_minimum_required(VERSION 2.8.9)
#SET(CMAKE_C_COMPILER /opt/hisi-linux/x86-arm/aarch64-himix100-linux/bin/aarch64-himix100-linux-gcc)
#SET(CMAKE_CXX_COMPILER /opt/hisi-linux/x86-arm/aarch64-himix100-linux/bin/aarch64-himix100-linux-g++)

project(http_server_demo)

set(CMAKE_CXX_STANDARD 11)
add_compile_options("-O2")

if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release")
endif()

add_executable(http_server_demo http_server_demo.cpp)
target_link_libraries(http_server_demo pthread)

install(DIRECTORY http-server-demo-pics DESTINATION ${CMAKE_INSTALL_BINDIR}/examples/http-server-demo)
install(TARGETS http_server_demo DESTINATION  ${CMAKE_INSTALL_BINDIR}/examples/http-server-demo)

