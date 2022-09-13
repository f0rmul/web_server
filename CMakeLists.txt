cmake_minimum_required(VERSION 3.20)
project("web-server")

set(3RD_PARTY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third_party)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(third_party)
add_subdirectory(src)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
