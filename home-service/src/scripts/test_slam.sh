# workspace
catkin_ws="/home/workspace/catkin_ws"

# launch turtlebot_world.launch
xterm -e "cd ${catkin_ws} && source devel/setup.bash && roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=${catkin_ws}/src/map/home.world" &

sleep 5

# launch gmapping_demo.launch
xterm -e "cd ${catkin_ws} && source devel/setup.bash && roslaunch turtlebot_gazebo gmapping_demo.launch" &

sleep 5

# launch view_navigation.launch
xterm -e "cd ${catkin_ws} && source devel/setup.bash && roslaunch turtlebot_rviz_launchers view_navigation.launch" &

sleep 5

# launch keyboard_teleop.launch
xterm -e "cd ${catkin_ws} && source devel/setup.bash && roslaunch turtlebot_teleop keyboard_teleop.launch"

