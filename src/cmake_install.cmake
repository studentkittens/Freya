<<<<<<< HEAD
# Install script for directory: /home/chris/Freya/src
=======
# Install script for directory: /home/christoph/dev/c++/Freya/src
>>>>>>> 07d5635ec1e6a7adcebd1c6d8fd48095b76c4ee0

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "/usr/local")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

# Install shared libraries without execute permission?
IF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  SET(CMAKE_INSTALL_SO_NO_EXE "0")
ENDIF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)

IF(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
<<<<<<< HEAD
  INCLUDE("/home/chris/Freya/src/AvahiBrowser/cmake_install.cmake")
  INCLUDE("/home/chris/Freya/src/LogHandler/cmake_install.cmake")
  INCLUDE("/home/chris/Freya/src/Config/cmake_install.cmake")
  INCLUDE("/home/chris/Freya/src/MPD/cmake_install.cmake")
=======
  INCLUDE("/home/christoph/dev/c++/Freya/src/AvahiBrowser/cmake_install.cmake")
  INCLUDE("/home/christoph/dev/c++/Freya/src/LogHandler/cmake_install.cmake")
  INCLUDE("/home/christoph/dev/c++/Freya/src/Config/cmake_install.cmake")
  INCLUDE("/home/christoph/dev/c++/Freya/src/MPD/cmake_install.cmake")
>>>>>>> 07d5635ec1e6a7adcebd1c6d8fd48095b76c4ee0

ENDIF(NOT CMAKE_INSTALL_LOCAL_ONLY)

