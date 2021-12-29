cmake_minimum_required(VERSION 2.8.6 FATAL_ERROR)

if(COMMAND CMAKE_POLICY)
  CMAKE_POLICY(SET CMP0003 NEW)
  CMAKE_POLICY(SET CMP0004 NEW)
endif(COMMAND CMAKE_POLICY)

project (ck_gazebo_sim)
include(GNUInstallDirs)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
)
catkin_package()
include_directories(${catkin_INCLUDE_DIRS})

find_package(gazebo REQUIRED)
include_directories(${GAZEBO_INCLUDE_DIRS})
link_directories(${GAZEBO_LIBRARY_DIRS})
list(APPEND CMAKE_CXX_FLAGS "${GAZEBO_CXX_FLAGS}")


find_package(ignition-msgs1 QUIET)
if (NOT ignition-msgs1_FOUND)
  message(FATAL_ERROR "Looking for ignition-msgs1-config.cmake - not found")
else()
  message(STATUS "Looking for ignition-msgs1-config.cmake - found")
endif()
include_directories(${IGNITION-MSGS_INCLUDE_DIRS})
link_directories(${IGNITION-MSGS_LIBRARY_DIRS})

find_package(ignition-transport4 QUIET)
if (NOT ignition-transport4_FOUND)
  message(FATAL_ERROR "Looking for ignition-transport4-config.cmake - not found")
else()
  message(STATUS "Looking for ignition-transport4-config.cmake - found")
endif()
include_directories(${IGNITION-TRANSPORT_INCLUDE_DIRS})
link_directories(${IGNITION-TRANSPORT_LIBRARY_DIRS})


add_subdirectory(2016)

