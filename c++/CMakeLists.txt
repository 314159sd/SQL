cmake_minimum_required( VERSION 3.22)
project( sql)

set (LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib)


file(GLOB SRC ${CMAKE_CURRENT_SOURCE_DIR}/usr/*)
add_library(library SHARED ${SRC})
target_link_libraries(library mysqlcppconn)

link_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/usr)

add_executable(usr user.cpp)
target_link_libraries(usr library)

add_executable(customer customer.cpp)
target_link_libraries(customer library)