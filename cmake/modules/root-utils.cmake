function(add_par PACKAGE)
  if(PACKAGE)
  message(STATUS "Generating ${PACKAGE}")
  add_custom_target(${PACKAGE}.par
      COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_SOURCE_DIR}/pars/${PACKAGE}
    COMMAND sed -e 's,include ..ROOTSYS./\\\(etc\\|test\\\)/Makefile.arch,include Makefile.arch,\; s/PACKAGE = */PACKAGE = ${PACKAGE}/\; s,SRCS *=.*,SRCS = ${SRCS},\;' < ${CMAKE_SOURCE_DIR}/cmake/par/Makefile.in | sed -e 's,HDRS *=.*,HDRS = ${HDRS},\; s,FSRCS *=.*,FSRCS = ${FSRCS},\; s,DHDR *=.*,DHDR = ${DHDR},\; s,EINCLUDE *:=.*,EINCLUDE := ${saveEINCLUDE},' > ${CMAKE_SOURCE_DIR}/pars/${PACKAGE}/Makefile
    COMMAND cp -pR `root-config --etcdir`/Makefile.arch ${CMAKE_SOURCE_DIR}/pars/${PACKAGE}/Makefile.arch
    COMMAND cp -pR ${CMAKE_SOURCE_DIR}/src/root/${PACKAGE}/* ${CMAKE_SOURCE_DIR}/pars/${PACKAGE}/
    COMMAND ${CMAKE_COMMAND} -E chdir ${CMAKE_SOURCE_DIR}/pars tar --exclude=.svn -czhf ${CMAKE_SOURCE_DIR}/pars/${PACKAGE}.par ${PACKAGE}
    COMMAND ${CMAKE_COMMAND} -E chdir ${CMAKE_SOURCE_DIR}/pars rm -rf ${PACKAGE}
    COMMAND ${CMAKE_COMMAND} -E cmake_echo_color --red --bold "${PACKAGE}.par has been created in ${CMAKE_SOURCE_DIR}/pars"
#    DEPENDS ${PARSRCS}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  )

  add_dependencies(par-all ${PACKAGE}.par)

  endif(PACKAGE)
endfunction(add_par PACKAGE)
