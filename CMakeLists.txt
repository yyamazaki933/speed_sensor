cmake_minimum_required(VERSION 2.8.3)
project(speed_sensor_driver)

## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  geometry_msgs
)

catkin_package(
)

include_directories(
  ${catkin_INCLUDE_DIRS}
)

add_executable(speed_sensor_driver src/speed_sensor_node.cpp src/serial.cpp)
target_link_libraries(speed_sensor_driver ${catkin_LIBRARIES})
