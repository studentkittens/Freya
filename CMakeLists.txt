CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(Freya CXX)

# Include pkg-config
INCLUDE(FindPkgConfig)
INCLUDE(CheckCXXCompilerFlag)
# some comment

# ------------------------------------------------
# Versioning 
# ------------------------------------------------
SET(FREYA_VERSION_MAJOR "0")
SET(FREYA_VERSION_MINOR "0")
SET(FREYA_VERSION_MICRO "1")
SET(FREYA_VERSION_NAME  "Terrifying Tarantula") 
# ------------------------------------------------

# ------------------------------------------------
# You can configure the next few params on the cmd:
# -DLIB_SUFFIX="64" for example
# ------------------------------------------------
IF(NOT DEFINED INSTALL_BIN_DIR)
 SET(INSTALL_BIN_DIR bin)
ELSE()
  MESSAGE("-- Install binaries to: \"${INSTALL_BIN_DIR}\"")
ENDIF()

IF(NOT DEFINED INSTALL_LIB_DIR)
  SET(INSTALL_LIB_DIR lib${LIB_SUFFIX})
ELSE()
  MESSAGE("-- Install library to: \"${INSTALL_LIB_DIR}\"")
ENDIF()

IF(NOT DEFINED INSTALL_INC_DIR)
  SET(INSTALL_INC_DIR include)
ELSE()
  MESSAGE("-- Install headers to: \"${INSTALL_INC_DIR}\"")
ENDIF()

IF(DEFINED LIB_SUFFIX)
  MESSAGE("-- Library suffix is: \"${LIB_SUFFIX}\"")
ENDIF()
# ------------------------------------------------


# ------------------------------------------------
# CFlags and warnlevel / build config 
# ------------------------------------------------
SET(COMMON_FLAGS "-Wall -Wextra -std=c++0x -Wno-unused-parameter -pipe")
SET(CMAKE_CXX_FLAGS_RELEASE "${COMMON_FLAGS} ${CMAKE_CXX_FLAGS} -Os -s -march=native")
SET(CMAKE_CXX_FLAGS_DEBUG   "${COMMON_FLAGS} ${CMAKE_CXX_FLAGS} -ggdb3")
SET(CMAKE_CXX_FLAGS         "${COMMON_FLAGS} ${CMAKE_CXX_FLAGS}")
ADD_DEFINITIONS(${CMAKE_CXX_FLAGS})
# ------------------------------------------------

# ----------------------
# Find required deps
# ----------------------
PKG_CHECK_MODULES(GTKMM3_PACKAGE gtkmm-3.0 REQUIRED)
PKG_CHECK_MODULES(GLIBMM_PACKAGE glibmm-2.4 REQUIRED)
PKG_CHECK_MODULES(LIBMPDCLIENT libmpdclient REQUIRED)
PKG_CHECK_MODULES(LIBXML2_PACKAGE libxml-2.0 REQUIRED)
PKG_CHECK_MODULES(LIBNOTIFY_PACKAGE libnotify REQUIRED)
PKG_CHECK_MODULES(LIBGLYR_PACKAGE libglyr REQUIRED)

INCLUDE_DIRECTORIES(${GTKMM3_PACKAGE_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(${GLIBMM_PACKAGE_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(${LIBMPDCLIENT_PACKAGE_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(${LIBXML2_PACKAGE_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(${LIBNOTIFY_PACKAGE_INCLUDE_DIRS})

# --------------------------
# set directories
# --------------------------
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin CACHE PATH "Single Directory for all Libraries")
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin CACHE PATH "Single Directory for all Executables.")

# --------------------------
# cxxtest - Tip from: http://battlemidget.blogspot.com/2010/03/c-cxxtest-cmake.html
# --------------------------
FIND_PACKAGE(CxxTest)
IF(CXXTEST_FOUND)
    FIND_PACKAGE(Perl QUIET)
    INCLUDE_DIRECTORIES(${CXXTEST_INCLUDE_DIR})
    ENABLE_TESTING()
ENDIF()

ADD_CUSTOM_TARGET(doc 
    COMMAND doxygen ${PROJECT_SOURCE_DIR}/FreyaDoxygen.conf
    COMMENT "Generate Doxygen doc" VERBATIM
    )

ADD_CUSTOM_TARGET(tex 
    COMMAND cd ${PROJECT_SOURCE_DIR}/doc/architecture && pdflatex -output-directory out/ doku.tex 
    COMMENT "Generate Latex documents" VERBATIM
    )

# --------------------------
# Add src/CMakeLists.txt
# --------------------------
ADD_SUBDIRECTORY(src)


# --------------------------
# uninstall target
# --------------------------
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
    IMMEDIATE @ONLY
    )

ADD_CUSTOM_TARGET(uninstall COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)

# --------------------------
# dest target
# --------------------------

ADD_CUSTOM_TARGET(release COMMAND "ruby" "scripts/amalgamation.rb > ${CMAKE_CURRENT_SOURCE_DIR}/src/Utils/CompileSymbols.cc")

# --------------------------
# dest target
# --------------------------
SET(ARCHIVE_NAME ${CMAKE_PROJECT_NAME}-${PROJECT_VERSION})
ADD_CUSTOM_TARGET(dist
    COMMAND git archive --prefix=${CMAKE_PROJECT_NAME}/ HEAD
        | bzip2 > ${CMAKE_BINARY_DIR}/${ARCHIVE_NAME}.tar.bz2
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

