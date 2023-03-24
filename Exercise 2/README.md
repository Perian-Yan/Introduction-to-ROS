# Exercise 2

## Demonstration

## Instructions
- Setup: download and unzip package `smb_highlevel_controller` to the `~/Workspaces/smb_ws/src` directory
- Create a subscriber to the `/scan` topic

  - Inspect the message type of `/scan` in [API documentation](http://docs.ros.org/en/melodic/api/sensor_msgs/html/msg/LaserScan.html), or use `rostopic type` 
after launching


  ```shell
  # launch the empty world
  roslaunch smb_gazebo smb_gazebo.launch
  
  # in a new terminal
  rostopic type /scan
  ```
  
  - Add a parameter file [config.yaml](https://github.com/Perian-Yan/Introduction-to-ROS/blob/36cbe4b5c018e1c7269894053d80dc6c9d76f237/Exercise%202/smb_highlevel_controller/config/config.yaml) with topic name and queue size for the subscriber
  
  - Get parameter using `.getParam()`
  
  ```cpp
  nodeHandle_.getParam("topic", topic)
  nodeHandle_.getParam("queue_size", queue_size)
  ```
  
  - Create subscriber
  
  ```cpp
  ros::Subscriber subscriber_ = nodeHandle_.subscribe(topic, queue_size, &SmbHighlevelController::ScanCallback, this);
  ```
  
  - Create [callback method](https://github.com/Perian-Yan/Introduction-to-ROS/blob/36cbe4b5c018e1c7269894053d80dc6c9d76f237/Exercise%202/smb_highlevel_controller/src/SmbHighlevelController.cpp#L29) that outputs the smallest distance measurement
  
  ```cpp
  void ScanCallback(const sensor_msgs::LaserScan &msg)
  ```
  
    👍 Implement the subscriber and the callback method as [class memebers](https://github.com/Perian-Yan/Introduction-to-ROS/blob/36cbe4b5c018e1c7269894053d80dc6c9d76f237/Exercise%202/smb_highlevel_controller/include/smb_highlevel_controller/SmbHighlevelController.hpp#L28-L34). 

- Create [launch file](https://github.com/Perian-Yan/Introduction-to-ROS/blob/36cbe4b5c018e1c7269894053d80dc6c9d76f237/Exercise%202/smb_highlevel_controller/launch/smb_highlevel_controller_node.launch):
  - Run the `smb_highlevel_controller` node
  - Load the parameter file
  - Include the launch file from Exercise 1. 
  - Pass the argument `laser_enabled` with the value `True`
  - Add RViz
  
- OPTIONAL
  - The [`pointcloud_to_laserscan` node](http://wiki.ros.org/pointcloud_to_laserscan) converts 3D point cloud into 2D laser scan
  - Create an additional subscriber to the topic `/rslidar_points` and print the number of points
