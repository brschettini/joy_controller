cmake_minimum_required(VERSION 2.8.3)
project(joy_controller)


find_package(catkin REQUIRED COMPONENTS
  joy
  roscpp
  std_msgs
  message_generation
)


 add_message_files(
   DIRECTORY
   msg
   FILES
   Joymsg.msg
 )

## Generate services in the 'srv' folder
# add_service_files(
#   FILES
#   Service1.srv
#   Service2.srv
# )

## Generate actions in the 'action' folder
# add_action_files(
#   FILES
#   Action1.action
#   Action2.action
# )

 generate_messages(
   DEPENDENCIES
   std_msgs
 )

catkin_package(
#  INCLUDE_DIRS include
  LIBRARIES joy_controller
  CATKIN_DEPENDS message_runtime
#  DEPENDS system_lib
)

include_directories(
  ${catkin_INCLUDE_DIRS}
)

add_executable(teleop_joymsg src/teleop_joymsg.cpp)
target_link_libraries(teleop_joymsg ${catkin_LIBRARIES})
add_executable(joymsg_float64 src/joymsg_float64.cpp)
target_link_libraries(joymsg_float64 ${catkin_LIBRARIES})
