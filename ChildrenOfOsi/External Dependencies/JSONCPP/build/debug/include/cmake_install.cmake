# Install script for directory: /home/anpbarr/jsoncpp-master/include

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/json" TYPE FILE FILES
    "/home/anpbarr/jsoncpp-master/include/json/allocator.h"
    "/home/anpbarr/jsoncpp-master/include/json/assertions.h"
    "/home/anpbarr/jsoncpp-master/include/json/autolink.h"
    "/home/anpbarr/jsoncpp-master/include/json/config.h"
    "/home/anpbarr/jsoncpp-master/include/json/features.h"
    "/home/anpbarr/jsoncpp-master/include/json/forwards.h"
    "/home/anpbarr/jsoncpp-master/include/json/json.h"
    "/home/anpbarr/jsoncpp-master/include/json/reader.h"
    "/home/anpbarr/jsoncpp-master/include/json/value.h"
    "/home/anpbarr/jsoncpp-master/include/json/version.h"
    "/home/anpbarr/jsoncpp-master/include/json/writer.h"
    )
endif()

