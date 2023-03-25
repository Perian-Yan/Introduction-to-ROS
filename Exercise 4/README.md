# Exercise 4

## Overview

## Demostration

## Instructions

- The node `/ekf_localization` uses measurements from wheel odometry, IMU sensor, and visual odometry to estimate the 3D robot pose by extended kalman filter
  ```shell
  # launch the file from exercise 3
  # in a new terminal
  rosnode info /ekf_localization
  ```
  - Publications:
    - `/odometry/filtered [nav_msgs/Odometry]`
  - Subscriptions:
    - `imu/data [sensor_msgs/Imu]`: 3D orientation
    - `smb_velocity_controller/odom [nav_msgs/Odometry]`: 2D pose from wheel

-  Use [`rqt_multiplot`](https://github.com/ANYbotics/rqt_multiplot_plugin) to plot the path of simulated robot in xy-plane
  - Install multiplot and run it
  
  ```shell
  # install
  sudo apt-get install ros-noetic-rqt-multiplot
  # run
  rqt_multiplot
  ```
  
  - New configuration -> configure plot -> add curve -> save configuration as
  <img width="700" alt="first" src="https://user-images.githubusercontent.com/100858995/227711492-ddc38be1-1259-45fd-93d8-df0667d98e69.png">
  
  <img width="483" alt="add curve" src="https://user-images.githubusercontent.com/100858995/227711500-e400c84b-dec8-4ec4-a03c-825d725c0515.png"> 
  
  <img width="650" alt="Snipaste_2023-03-25_11-18-02" src="https://user-images.githubusercontent.com/100858995/227711524-111c0536-0136-4133-b122-20ed334e666e.png">

- Download the rosbag `smb_navigation.bag` from the course website and inspect it
  ```shell
  rosbag info smb_navigation.bag
  ```

- Create a new launch file that starts the node [`ekf_localization_node`](https://github.com/Perian-Yan/Introduction-to-ROS/blob/d4945f333096095403d05b5cfd78ea1bdb59de9d/Exercise%204/src/smb_highlevel_controller/launch/ekf_localization.launch#L2-L5)

- Use `rqt_multiplot` to plot the path of the recorded robot

  ```shell
  # set the parameter `/use_sim_time` to true
  rosparam set use_sim_time true
  # play the bag file 
  rosbag play smb_navigation.bag --clock
  ```
  
  ![recorded_smb_xy](https://user-images.githubusercontent.com/100858995/227726913-b6e90f17-ca4a-4751-b8b7-d8f336673003.png)

  
- Add a new launch file (refer to the [control.launch](https://github.com/Perian-Yan/Introduction-to-ROS/blob/d4945f333096095403d05b5cfd78ea1bdb59de9d/Exercise%204/src/smb_common/smb_control/launch/control.launch)):
  - Add a [`robot_state_publisher` node]([http://wiki.ros.org/robot_state_publisher/Tutorials/Using%20the%20robot%20state%20publisher%20on%20your%20own%20robot](https://github.com/Perian-Yan/Introduction-to-ROS/blob/d4945f333096095403d05b5cfd78ea1bdb59de9d/Exercise%204/src/smb_highlevel_controller/launch/ekf_localization.launch#L40-L44)). See the reference [here](http://wiki.ros.org/robot_state_publisher/Tutorials/Using%20the%20robot%20state%20publisher%20on%20your%20own%20robot)
  - Add a frame named [`smb_top_view`](https://github.com/Perian-Yan/Introduction-to-ROS/blob/d4945f333096095403d05b5cfd78ea1bdb59de9d/Exercise%204/src/smb_highlevel_controller/launch/ekf_localization.launch#L16-L18). See [here, section 6.3](http://wiki.ros.org/tf)
  - [`/use_sim_time`](https://github.com/Perian-Yan/Introduction-to-ROS/blob/d4945f333096095403d05b5cfd78ea1bdb59de9d/Exercise%204/src/smb_highlevel_controller/launch/ekf_localization.launch#L7) can be set true in launch file
  - Add [`rqt_multiplot`](https://github.com/Perian-Yan/Introduction-to-ROS/blob/d4945f333096095403d05b5cfd78ea1bdb59de9d/Exercise%204/src/smb_highlevel_controller/launch/ekf_localization.launch#L12-L14)
  - OPTIONAL 👏 [Play the bag](https://github.com/Perian-Yan/Introduction-to-ROS/blob/d4945f333096095403d05b5cfd78ea1bdb59de9d/Exercise%204/src/smb_highlevel_controller/launch/ekf_localization.launch#L20-L22) at 50% of the nominal speed
