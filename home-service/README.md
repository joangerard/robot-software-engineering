# Home Service

The package is about a turtlebot robot put on a customized environment that navigates from one point to another simulating to pick up an object and to drop it off. This packages uses amcl to localize the robot using a set of particles that are estimations of the robot's location, it also uses SLAM to create a 2D map of the environment, it uses the ROS Navigation Stack to navigate from one point in the environment to another, this plans the path of the robot trajectory using Dijsktra's algorithm to find the shortest path between two points. 

## Used Packages

The project uses the following packages:

- gmapping: it provides laser-based SLAM to create a 2-D occupacy map of the environment. It takes as input the odometry data + laser range-finder measurements and it publishes an occupancy grid map. 
- amcl: it uses the Active Monte Carlo Localization algorithm to localize a robot in the environment. It is based on a probabilistic algorithm called the particle filter that uses a set of particles to estimate the posterior distribution.
- turtlebot: low-cost, personal robot kit with open-source software. 
- turtlebot_teleop: it launches a console that receives key inputs in order to navigate the robot manually through the environment. 
- turtlebot_simulator: it is in charge of launching a TurtleBot robot into Gazebo. 
- turtlebot_interactions: visualisation and interactive tools for the TurtleBot.
- turtlebot_rviz_launchers: it launches rviz to visualize the robot, map, costmaps, laser measurements, navigation, etc.

The project also creates two packages: 

- add_makers: It publishes a marker into the pick-up zone, then it deletes it for 5 seconds and then it publishes a marker into the drop-off zone. 
- pick_objects: the robot navigates to the picked-up zone, it stays there for 5 seconds and then it navigates to the drop-off zone. 

## Scripts 

This scripts help to avoid instantiating terminals and launching ros on each of them manually, it uses `xterm`. The scripts generally launches Gazebo using the created virtual environment, it spaws the turtlebot robot there, it launches rviz (sometimes with a custom configuration file), and then it performs the task. 

### home_service.sh
The robot transports a virtual object from the pick-up zone to the drop-off zone. The virtual object is represented by a marker in the environment which is a cube in this case. First, the marker is published in the pick-up zone, the robot navigates to such zone, the marker disappears, representing that the robot has picked up the virtual object, the robot then navigates to the drop-off zone, and finally, the mark appears again in such zone, representing that the robot has dropped off the virtual object. It combines the pick_objects and add_makers packages.

### pick_objects.sh
The robot navigates to the pick-up zone, it waits there for 5 seconds to simulate to pick up an object and then it goes to tthe drop-off zone.

### add_marker.sh
It publishes a marker into the pick-up zone, then it deletes it for 5 seconds and then it publishes a marker into the drop-off zone. 

### test_navigation.sh
It test navigation and localization. Once the script is launched and rviz opened, select a 2D navigation goal. 


### test_slam.sh
With this script you can manually test SLAM. A map of the environment can be created and saved to be used for the localization and navigation part. 


### How to run the scripts?

To run the scripts just execute: 

```
$ cd catkin_ws/src/scripts
$ chmod +x home_service.sh
$ ./home_service.sh
```

## Installation
Add the following packages via Git:

```
cd catkin_ws/src
git clone https://github.com/ros-perception/slam_gmapping.git  
git clone https://github.com/turtlebot/turtlebot.git  
git clone https://github.com/turtlebot/turtlebot_interactions.git  
git clone https://github.com/turtlebot/turtlebot_simulator.git 
```