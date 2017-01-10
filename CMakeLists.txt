project(openmd-utils)
cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

set(CPACK_PACKAGE_VERSION_MAJOR "0")
set(CPACK_PACKAGE_VERSION_MINOR "2")
set(CPACK_PACKAGE_VERSION_PATCH "0")
set(CPACK_PACKAGE_VERSION_RELEASE "2")
set(CMAKE_INSTALL_LIBDIR lib64)

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/cmake/openmd-utils.spec.in"
  "${PROJECT_SOURCE_DIR}/openmd-utils.spec"
  )
  
  configure_file (
  "${PROJECT_SOURCE_DIR}/cmake/omd.sh.in"
  "${PROJECT_BINARY_DIR}/omd.sh"
  )

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++1y" COMPILER_SUPPORTS_CXX1Y)
if(COMPILER_SUPPORTS_CXX1Y)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y")
else()
    message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-parameter -Wno-unused-variable -Wno-reorder -Wno-sign-compare")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic")

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules")
find_package(Qhull REQUIRED)
find_package(OPENMD REQUIRED)
find_package(ROOT REQUIRED)
find_package(ROOT REQUIRED)
string(REPLACE "." ";" VERSION_LIST ${ROOT_VERSION})
list(GET VERSION_LIST 0 ROOT_VERSION_MAJOR)
if (ROOT_VERSION_MAJOR GREATER 5)
  include(Root6Macros)
endif (ROOT_VERSION_MAJOR GREATER 5)
include(RootMacros)

add_custom_target(par-all ALL)

add_subdirectory(src/root/OmdBase)

set(CPACK_SOURCE_GENERATOR "TGZ")
set(CPACK_SOURCE_PACKAGE_FILE_NAME
  "${CMAKE_PROJECT_NAME}-${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}")
set(CPACK_SOURCE_IGNORE_FILES
  "/build/;/.git/;/tmp/;~$;${CPACK_SOURCE_IGNORE_FILES}")
add_custom_target(dist COMMAND ${CMAKE_MAKE_PROGRAM} package_source)

include(CPack)

# add openmd include dir and src dir of this project
set(MY_INCLUDE_DIRS
	${OPENMD_INCLUDE_DIRS}
	${ROOT_INCLUDE_DIR}
	${PROJECT_SOURCE_DIR}/src
)

set (MY_LINK_DIRS
${CMAKE_CURRENT_BINARY_DIR}
${ROOT_LIBRARY_DIR}
)

include_directories( ${MY_INCLUDE_DIRS})
link_directories( ${MY_LINK_DIRS})

set (DUMP2ROOTSOURCE
    src/applications/dump2Root/Dump2Root.cpp
    src/applications/dump2Root/Dump2RootCmd.cpp
    src/visitors/RootVisitor.cpp
)

add_executable(Dump2Root ${DUMP2ROOTSOURCE})
target_link_libraries(Dump2Root openmd_single openmd_core openmd_single ${QHULL_LIBRARIES} ${ROOT_LIBRARIES} -lGeom OmdBase)

install(TARGETS Dump2Root 
RUNTIME DESTINATION bin COMPONENT RUNTIME
LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT RUNTIME
ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT DEVELOPMENT)

SET(OPENMD_SHARE_DIR share/openmd-utils)
install(FILES pars/OmdBase.par DESTINATION ${OPENMD_SHARE_DIR}/pars)
FILE(GLOB macros "${CMAKE_CURRENT_SOURCE_DIR}/macros/*.C")
install(FILES ${macros} DESTINATION ${OPENMD_SHARE_DIR}/macros)
FILE(GLOB blender "${CMAKE_CURRENT_SOURCE_DIR}/src/blender/openmd/*.py")
install(FILES ${blender} DESTINATION ${OPENMD_SHARE_DIR}/blender/openmd)
install(PROGRAMS scripts/omd-run DESTINATION bin)
install(PROGRAMS ${CMAKE_BINARY_DIR}/omd.sh DESTINATION /etc/profile.d)

# uninstall
CONFIGURE_FILE(
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake/cmake_uninstall.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
  IMMEDIATE @ONLY)

ADD_CUSTOM_TARGET(uninstall
  "${CMAKE_COMMAND}" -P "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake")
