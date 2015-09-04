cmake_minimum_required(VERSION 2.8.3)
project(ci2cv)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  cv_bridge
  image_transport
  roscpp
  sensor_msgs
  std_msgs
  usb_cam
 # filesystem 
#  system
)
#find_package(Boost REQUIRED COMPONENTS )
include_directories(
  ${catkin_INCLUDE_DIRS}
)
link_directories(${catkin_LIBRARY_DIRS})
#set (EXTRA_LIBS ${EXTRA_LIBS} utils)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I/home/lina/opencv-2.4.11/build/include -I/home/lina/setup/face-analysis-sdk-master/src/ -I/home/lina/catkin_ws/src/ci2cv/src/ -I/home/lina/setup/face-analysis-sdk-master/src/qt-gui/ -I/usr/include/qt4/")
SET(CI2CV_LIBRARY avatarAnim  clmTracker utilities -L/home/lina/setup/face-analysis-sdk-master/build/lib/)
SET(OpenCV_LIBS opencv_core opencv_imgproc opencv_highgui -L/home/lina/opencv-2.4.11/build/lib/)
SET(HEADERS_THREE src/utils/utils.cpp)
SET(HEADERS_FOUR src/utils/utils.h)
SET(HEADERS_ONE src/GroupPicture.cpp)
SET(HEADERS_TWO src/GroupPicture.h)


add_executable(ci2cv_node src/main.cpp ${HEADERS_ONE} ${HEADERS_TWO} ${HEADERS_THREE} ${HEADERS_FOUR})
add_executable(ci2cv_publisher src/publisher.cpp ${HEADERS_ONE} ${HEADERS_TWO} ${HEADERS_THREE} ${HEADERS_FOUR})
target_link_libraries(ci2cv_node
 ${catkin_LIBRARIES} ${LIBS} ${OpenCV_LIBS} ${CI2CV_LIBRARY} )
target_link_libraries(ci2cv_publisher
 ${catkin_LIBRARIES} ${LIBS} ${OpenCV_LIBS} ${CI2CV_LIBRARY} )
##${Boost_FILESYSTEM_LIBRARY} ${Boost_SYSTEM_LIBRARY}
#############
## Install ##
#############

# all install targets should use catkin DESTINATION variables
# See http://ros.org/doc/api/catkin/html/adv_user_guide/variables.html

## Mark executable scripts (Python etc.) for installation
## in contrast to setup.py, you can choose the destination
# install(PROGRAMS
#   scripts/my_python_script
#   DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
# )

## Mark executables and/or libraries for installation
# install(TARGETS ci2cv ci2cv_node
#   ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#   LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#   RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
# )

## Mark cpp header files for installation
# install(DIRECTORY include/${PROJECT_NAME}/
#   DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
#   FILES_MATCHING PATTERN "*.h"
#   PATTERN ".svn" EXCLUDE
# )

## Mark other files for installation (e.g. launch and bag files, etc.)
# install(FILES
#   # myfile1
#   # myfile2
#   DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
# )

#############
## Testing ##
#############

## Add gtest based cpp test target and link libraries
# catkin_add_gtest(${PROJECT_NAME}-test test/test_ci2cv.cpp)
# if(TARGET ${PROJECT_NAME}-test)
#   target_link_libraries(${PROJECT_NAME}-test ${PROJECT_NAME})
# endif()

## Add folders to be run by python nosetests
# catkin_add_nosetests(test)
