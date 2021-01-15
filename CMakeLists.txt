cmake_minimum_required(VERSION 2.8.3)
project(robot_control)
add_definitions(-std=c++11)
set(CMAKE_BUILD_TYPE "Debug")
find_package(catkin REQUIRED COMPONENTS roscpp std_msgs geometry_msgs)

include_directories("/home/nvidia/catkin_new/devel/include")
include_directories("../include/robot_control")
include_directories(${catkin_INCLUDE_DIRS} )
link_directories(${catkin_LIBRARY_DIRS})


catkin_package(CATKIN_DEPENDS message_runtime std_msgs geometry_msgs)

add_executable(testControl src/testControl.cc src/Controller.cc)
target_link_libraries(testControl ${catkin_LIBRARIES})
install(TARGETS testControl
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})

add_executable(angleControl src/AngleFollowControl.cc src/Controller.cc src/LocOpenpose.cc src/ultils.cc)
target_link_libraries(angleControl ${catkin_LIBRARIES})
install(TARGETS angleControl
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})

add_executable(LyPositionControl src/LyPositionControl.cc src/Controller.cc src/ultils.cc)
target_link_libraries(LyPositionControl ${catkin_LIBRARIES})
install(TARGETS LyPositionControl
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})
  
add_library(mpcBase SHARED src/mpcbase/Adaptive_data.c
  src/mpcbase/Adaptive.c src/mpcbase/rt_nonfinite.c 
  src/mpcbase/rtGetInf.c src/mpcbase/rtGetNaN.c)
install(TARGETS mpcBase LIBRARY DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})

add_executable(mpcControl src/testMPCControl.cc)
target_link_libraries(mpcControl mpcBase)
install(TARGETS mpcControl
RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})


add_executable(MPCTraTrackControl src/MPCTraTrackControl.cc src/Controller.cc src/ultils.cc)
target_link_libraries(MPCTraTrackControl ${catkin_LIBRARIES} mpcBase)
install(TARGETS MPCTraTrackControl
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})

add_executable(MPCFollowControl src/MPCFollowControl.cc src/Controller.cc src/ultils.cc)
target_link_libraries(MPCFollowControl ${catkin_LIBRARIES} mpcBase)
install(TARGETS MPCFollowControl
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})


add_executable(FiniteTimeControl src/FiniteTimeControl.cc src/Controller.cc src/ultils.cc)
target_link_libraries(FiniteTimeControl ${catkin_LIBRARIES})
install(TARGETS FiniteTimeControl
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})

add_executable(testNothing src/test.cc src/ultils.cc)
target_link_libraries(testNothing -lpthread)
install(TARGETS testNothing
RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})

add_executable(LineFollowControl src/LineFollowControl.cc src/Controller.cc src/LocOpenpose.cc src/ultils.cc)
target_link_libraries(LineFollowControl ${catkin_LIBRARIES})
install(TARGETS LineFollowControl
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})