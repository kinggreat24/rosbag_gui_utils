cmake_minimum_required(VERSION 3.0.2)
project(rosbag_utils_gui)

## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  cv_bridge
  nav_msgs
  roscpp
  rospy
  rviz
  sensor_msgs
  std_msgs
  tf
  rosmaster
  rosbag
  pcl_conversions
  pcl_ros
  pcl_msgs
)

## System dependencies are found with CMake's conventions
# find_package(Boost REQUIRED COMPONENTS system)

find_library(BOOST_SERIALIZATION boost_serialization)
if(NOT BOOST_SERIALIZATION)
  message(FATAL_ERROR "Can't not find libboost_serialization")
endif()

# QT Library for aruco marker display
if(rviz_QT_VERSION VERSION_LESS "5")
  message(STATUS "Using Qt4 based on the rviz_QT_VERSION: ${rviz_QT_VERSION}")
  find_package(Qt4 ${rviz_QT_VERSION} EXACT REQUIRED QtCore QtGui)
  ## pull in all required include dirs, define QT_LIBRARIES, etc.
  include(${QT_USE_FILE})
else()
  message(STATUS "Using Qt5 based on the rviz_QT_VERSION: ${rviz_QT_VERSION}")
  find_package(Qt5 ${rviz_QT_VERSION} EXACT REQUIRED Core Widgets)
  ## make target_link_libraries(${QT_LIBRARIES}) pull in all required dependencies
  set(QT_LIBRARIES Qt5::Widgets)
endif()

##PCL
#set(PCL_DIR /usr/local/pcl_1.8/share/pcl-1.8)
find_package(PCL 1.7 REQUIRED QUIET)
add_definitions(${PCL_DEFINITIONS})
add_definitions(-DPCL_FOUND)
# message(STATUS "pcl include dir ${PCL_INCLUDE_DIRS}")
# message(STATUS "pcl libraries ${PCL_LIBRARIES}")


## I prefer the Qt signals and slots to avoid defining "emit", "slots",
## etc because they can conflict with boost signals, so define QT_NO_KEYWORDS here.
add_definitions(-DQT_NO_KEYWORDS)

## This setting causes Qt's "MOC" generation to happen automatically.
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

## Uncomment this if the package has a setup.py. This macro ensures
## modules and global scripts declared therein get installed
## See http://ros.org/doc/api/catkin/html/user_guide/setup_dot_py.html
# catkin_python_setup()



###################################
## catkin specific configuration ##
###################################
## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
## INCLUDE_DIRS: uncomment this if your package contains header files
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES rosbag_utils_gui
  CATKIN_DEPENDS cv_bridge nav_msgs roscpp rospy rviz sensor_msgs std_msgs tf rosbag
#  DEPENDS system_lib
)


###########
## Build ##
###########


## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
  include
  ${PCL_INCLUDE_DIRS}
  ${catkin_INCLUDE_DIRS}
)

FILE(GLOB_RECURSE RobbagUtilsPluginIncFiles "include/rosbag_utils_gui/*.h")
message(STATUS "RobbagUtilsPluginIncFiles: ${RobbagUtilsPluginIncFiles}")
aux_source_directory(src/. RobbagUtils_DIR_SRCS)
add_library(${PROJECT_NAME}_plugin 
  ${RobbagUtilsPluginIncFiles} 
  ${RobbagUtils_DIR_SRCS}
  ${MOC_FILES}
  )
target_link_libraries(${PROJECT_NAME}_plugin ${QT_LIBRARIES} ${PCL_LIBRARIES}  ${catkin_LIBRARIES} ${BOOST_SERIALIZATION})

install(TARGETS
  ${PROJECT_NAME}_plugin
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

install(FILES
  plugin_description.xml
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)