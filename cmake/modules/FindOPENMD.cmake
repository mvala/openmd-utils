# - Try to find OPENMD
# Once done this will define
#  OPENMD_FOUND - System has OPENMD
#  OPENMD_INCLUDE_DIRS - The OPENMD include directories
#  OPENMD_LIBRARIES - The libraries needed to use OPENMD


find_path(OPENMD_INCLUDE_DIR io/DumpReader.hpp
          HINTS $ENV{OPENMD_INCLUDE_DIR} /usr/include/openmd
          PATH_SUFFIXES OPENMD )

find_library(OPENMD_LIBRARY NAMES openmd_core OPENMD
             HINTS $ENV{OPENMD_LIB_DIR} /usr/lib64 )

set(OPENMD_LIBRARIES ${OPENMD_LIBRARY} )
set(OPENMD_INCLUDE_DIRS ${OPENMD_INCLUDE_DIR} )

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set OPENMD_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(OPENMD  DEFAULT_MSG
                                  OPENMD_LIBRARY OPENMD_INCLUDE_DIR)

mark_as_advanced(OPENMD_INCLUDE_DIR OPENMD_LIBRARY )

