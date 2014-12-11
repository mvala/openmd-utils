project(openmd-utils)
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-parameter -Wno-unused-variable -Wno-reorder")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic")

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules")
find_package(Qhull REQUIRED)
find_package(OPENMD REQUIRED)
#find_package(ROOT REQUIRED)

include(CPack)

# uninstall
CONFIGURE_FILE(
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake/cmake_uninstall.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
  IMMEDIATE @ONLY)

ADD_CUSTOM_TARGET(uninstall
  "${CMAKE_COMMAND}" -P "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake")

# add openmd include dir and src dir of this project
include_directories("${OPENMD_INCLUDE_DIRS}" "${PROJECT_SOURCE_DIR}/src")

set (DUMP2ROOTSOURCE
    src/applications/dump2Root/Dump2Root.cpp
    src/applications/dump2Root/Dump2RootCmd.cpp
    src/visitors/RootVisitor.cpp
)

add_executable(Dump2Root ${DUMP2ROOTSOURCE})
target_link_libraries(Dump2Root openmd_single openmd_core openmd_single ${QHULL_LIBRARIES})
