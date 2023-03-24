# Exercise 3

## Overview
The aim of this exercise is using sensor measurement `/scan` to control `/cmd_vel` the robot. I learned how to create the publisher and transform coordinates.

## Demonstration

The GREEN SPHERE Marker 🟢 is from rslidar frame (the easy way) and the BLUE CUBE 🟦 is from odom frame (the difficult way).



https://user-images.githubusercontent.com/100858995/227656627-a2894f43-cfc5-4399-8d99-fe5329ff80e8.mp4



## Instructions

- Adapt the launch file from the exercise 2
  - Remove the keyboard twist node
  - Load `singlePillar.world` as the world

- Create a publisher on the topic `/cmd_vel`
  - Add `geometry_msgs` as a dependency to CMakeLists.txt and package.xml
  - [Extract the position](https://github.com/Perian-Yan/Introduction-to-ROS/blob/50534f01f018d1eb1501578481053a6ee8e27d92/Exercise%203/src/smb_highlevel_controller/src/SmbHighlevelController.cpp#L62-L63) of the pillar w.r.t. the robot form laser scan. 
  - Write a [P controller](https://github.com/Perian-Yan/Introduction-to-ROS/blob/50534f01f018d1eb1501578481053a6ee8e27d92/Exercise%203/src/smb_highlevel_controller/src/SmbHighlevelController.cpp#L83-L90) that dirves the robot into the pillar. 
    - use `config.yaml` for controller gains
    - set gains as class members so that they can be used globally 
    - write the code in callback method of laser scan

- Publish a visualization marker in RViz that shows the estimated position of the pillar
  - (easy 😊) Publish the point in the [sensor frame rslidar](https://github.com/Perian-Yan/Introduction-to-ROS/blob/50534f01f018d1eb1501578481053a6ee8e27d92/Exercise%203/src/smb_highlevel_controller/src/SmbHighlevelController.cpp#L92-L93). RViz will automatically transform the marker into the odom frame
  - (difficult 😕) Publish the point in the [odom frame](https://github.com/Perian-Yan/Introduction-to-ROS/blob/50534f01f018d1eb1501578481053a6ee8e27d92/Exercise%203/src/smb_highlevel_controller/src/SmbHighlevelController.cpp#L117-L130) by implementing a [TF listener](http://wiki.ros.org/tf/Tutorials/Writing%20a%20tf%20listener%20%28C%2B%2B%29)

- Consult API document:
  - [geometry_msgs/Twist](http://docs.ros.org/en/api/geometry_msgs/html/msg/Twist.html)
  - [visualization_msgs/Marker](http://wiki.ros.org/rviz/DisplayTypes/Marker)

- For RViz:
  - Add plugins: TF, Robot Model, Laser Scan, and Marker
  - Save the configure and load it in the launch file
