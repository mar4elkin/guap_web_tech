cmake_minimum_required(VERSION 3.10)

project(EShop)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenSSL REQUIRED)
find_package(PkgConfig REQUIRED)
find_package(mongocxx REQUIRED)
find_package(bsoncxx REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/include/stb)
include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(/usr/local/include/mongocxx/v_noabi)
include_directories(/usr/local/include/bsoncxx/v_noabi)

file(GLOB SOURCES "src/*.cpp")

add_executable(EShop ${SOURCES})

target_link_libraries(EShop PRIVATE OpenSSL::Crypto mongo::mongocxx_shared mongo::bsoncxx_shared)

