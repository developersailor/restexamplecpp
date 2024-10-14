cmake_minimum_required(VERSION 3.12)

# vcpkg toolchain dosyasını ayarlayın (tam yol kullanın)
set(CMAKE_TOOLCHAIN_FILE "~/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")

project(rest_client)

find_package(cpprestsdk REQUIRED)
find_package(fmt CONFIG REQUIRED)

add_executable(rest_client rest_client.cpp)

target_link_libraries(rest_client PRIVATE cpprestsdk::cpprest fmt::fmt)