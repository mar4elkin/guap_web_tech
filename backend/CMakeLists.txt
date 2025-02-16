cmake_minimum_required(VERSION 3.10)

project(EShop)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenSSL REQUIRED)

find_package(PostgreSQL REQUIRED)

find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBPQXX REQUIRED libpqxx)

include_directories(${PostgreSQL_INCLUDE_DIRS} ${LIBPQXX_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/include/stb ${CMAKE_SOURCE_DIR}/src)

file(GLOB SOURCES "src/*.cpp")

add_executable(EShop ${SOURCES})

target_link_libraries(EShop ${PostgreSQL_LIBRARIES} ${LIBPQXX_LIBRARIES} OpenSSL::Crypto)

target_compile_options(EShop PRIVATE ${LIBPQXX_CFLAGS_OTHER})
