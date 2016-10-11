project(openmd-utils)
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

set(CPACK_PACKAGE_VERSION_MAJOR "0")
set(CPACK_PACKAGE_VERSION_MINOR "0")
set(CPACK_PACKAGE_VERSION_PATCH "1")

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/cmake/openmd-utils.spec.in"
  "${PROJECT_SOURCE_DIR}/openmd-utils.spec"
  )


set(CPACK_SOURCE_GENERATOR "TGZ")
set(CPACK_SOURCE_PACKAGE_FILE_NAME
  "${CMAKE_PROJECT_NAME}-${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}")
set(CPACK_SOURCE_IGNORE_FILES
  "/build/;/.git/;/tmp/;~$;${CPACK_SOURCE_IGNORE_FILES}")
add_custom_target(dist COMMAND ${CMAKE_MAKE_PROGRAM} package_source)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-parameter -Wno-unused-variable -Wno-reorder -Wno-sign-compare")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic")

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules")
find_package(Qhull REQUIRED)
find_package(OPENMD REQUIRED)
find_package(ROOT REQUIRED)
include(root-utils)

add_custom_target(par-all INSTALL)

include(CPack)

add_subdirectory(src/root/OmdBase)

# uninstall
CONFIGURE_FILE(
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake/cmake_uninstall.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
  IMMEDIATE @ONLY)

ADD_CUSTOM_TARGET(uninstall
  "${CMAKE_COMMAND}" -P "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake")

# add openmd include dir and src dir of this project
set(INCLUDE_DIRECTORIES
	${OPENMD_INCLUDE_DIRS}
	${ROOT_INCLUDE_DIR}
	${PROJECT_SOURCE_DIR}/src
)
include_directories( ${INCLUDE_DIRECTORIES})

set (DUMP2ROOTSOURCE
    src/applications/dump2Root/Dump2Root.cpp
    src/applications/dump2Root/Dump2RootCmd.cpp
    src/visitors/RootVisitor.cpp
)

add_executable(Dump2Root ${DUMP2ROOTSOURCE})
target_link_libraries(Dump2Root openmd_single openmd_core openmd_single ${QHULL_LIBRARIES} ${ROOT_LIBRARIES} Geom OmdBase)

install(TARGETS Dump2Root 
RUNTIME DESTINATION bin COMPONENT RUNTIME
LIBRARY DESTINATION lib64 COMPONENT RUNTIME
ARCHIVE DESTINATION lib64 COMPONENT DEVELOPMENT)

SET(OPENMD_SHARE_DIR share/openmd-utils)
install(FILES pars/OmdBase.par DESTINATION ${OPENMD_SHARE_DIR}/pars)
FILE(GLOB macros "${CMAKE_CURRENT_SOURCE_DIR}/macros/*.C")
install(FILES ${macros} DESTINATION ${OPENMD_SHARE_DIR}/macros)
install(FILES scripts/RunOpenMD.sh DESTINATION ${OPENMD_SHARE_DIR}/scripts)


