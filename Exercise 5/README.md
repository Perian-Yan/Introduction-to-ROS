# Exercise 5

## Overview

In this exercise, I learned how to create a service server and a client that can stop the robot based on distance from the pillar or the IMU data.

## Demonstration




https://user-images.githubusercontent.com/100858995/227747530-21f4fbf1-e947-467c-9af5-d6e507004af1.mp4




## Instructions

- Implement a service server that can stop and start the server
  - Use the [`std_srvs/SetBool`](http://docs.ros.org/en/noetic/api/std_srvs/html/srv/SetBool.html) service type
  - Load the service name from the [parameter server](https://github.com/Perian-Yan/Introduction-to-ROS/blob/e047ccad2cbb9be144bdc77a2faa9f91e4026266/Exercise%205/src/smb_highlevel_controller/config/config.yaml#L10-L11)
  - Create the [callback method](https://github.com/Perian-Yan/Introduction-to-ROS/blob/40d734d955247446eb8a5961203f41ca82c5e914/Exercise%205/src/smb_highlevel_controller/src/SmbHighlevelController.cpp#L53-L64)
  - Launch the node and call the service
  
  ```shell
  # launch
  roslaunch smb_highlevel_controller smb_highlevel_controller_node.launch
  # call the service
  rosservice call /stop_smb 1   # 1 for stop, 0 for start
  ```
  
- OPTIONAL 👏 
  - Create a separate [node](https://github.com/Perian-Yan/Introduction-to-ROS/blob/40d734d955247446eb8a5961203f41ca82c5e914/Exercise%205/src/smb_highlevel_controller/src/StopClose.cpp) that stops the robot if it is too close to an obstacle using the laser measurements.
    - the robot will be stopped if the distance [less than 4](https://github.com/Perian-Yan/Introduction-to-ROS/blob/40d734d955247446eb8a5961203f41ca82c5e914/Exercise%205/src/smb_highlevel_controller/src/StopClose.cpp#L36-L42)
     
  - Create a separate [node](https://github.com/Perian-Yan/Introduction-to-ROS/blob/40d734d955247446eb8a5961203f41ca82c5e914/Exercise%205/src/smb_highlevel_controller/src/StopCrash.cpp) that stops the robot after a crash using the IMU data.
    - the robot will be stopped if the linear acceleration in x is [larger than 1.5](https://github.com/Perian-Yan/Introduction-to-ROS/blob/40d734d955247446eb8a5961203f41ca82c5e914/Exercise%205/src/smb_highlevel_controller/src/StopCrash.cpp#L14-L20) 
    
  - ❗ Remeber to add the two nodes as executables in [CMakeLists.txt](https://github.com/Perian-Yan/Introduction-to-ROS/blob/40d734d955247446eb8a5961203f41ca82c5e914/Exercise%205/src/smb_highlevel_controller/CMakeLists.txt#L50-L66)  
  - Run the nodes
    ```shell
    rosrun smb_highlevel_controller stop_close_client
    rosrun smb_highlevel_controller stop_crash_client
    ```
