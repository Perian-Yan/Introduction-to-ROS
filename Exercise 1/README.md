# Exercise 1
## Demonstration

## Instructions
- Setup SMB simulation
  - Download "smb_common.zip"
  - Unzip and place it in "~/Workspaces/smb_ws/src"
  - Build and source the package
  ```console
  ros@ros-vm:~Workspaces/smb_ws$ catkin build
  ros@ros-vm:~Workspaces/smb_ws$ source devel/setup.bash
  ```
  ❗ Use `catkin build` instead of `catkin_make`
  
- Launch the simulation (empty world)
  ```shell
  roslaunch smb_gazebo smb_gazebo.launch
  ```
  ❗ I encountered errors when launching (e.g. ERROR: cannot launch node of type [twist_mux/twist_mux]: twist_mux)
  
  Similar errors be solved by installing some packages:
  ```shell
  sudo apt install ros-noetic-twist-mux
  sudo apt install ros-noetic-robot-localization
  ```
  For more details please see [Exercise 1 Troubleshooting](https://github.com/Perian-Yan/Introduction-to-ROS/blob/274323fdd8e7d93eb660f9dd99ef3a9acddfd8c8/Exercise%201/Exercise-1-v2.pdf)
  
- Send velocity command to topic `/cmd_vel`
  ```
  # in a new terminal
  # use tab for auto-completion
  rostopic pub /cmd_vel geometry_msgs/Twist "linear:
  x: 0.2
  y: 0.0
  z: 0.0
  angular:
  x: 0.0
  y: 0.0
  z: 0.0
  ```
  
- Use `teleop_twist_keyboard`
  ```shell
  # directly git clone the new package to the src
  ros@ros-vm:~Workspaces/smb_ws/src$ git clone https://github.com/ros-teleop/teleop_twist_keyboard.git
  
  # or, symlink it
  ros@ros-vm:~Workspaces/smb_ws$ cd ~/git
  ros@ros-vm:~/git$ git clone https://github.com/ros-teleop/teleop_twist_keyboard.git
  ros@ros-vm:~/git$ cd ~/Workspaces/smb_ws/src
  ros@ros-vm:~Workspaces/smb_ws/src$ ln -s ~/git/teleop_twist_keyboard/
  ros@ros-vm:~Workspaces/smb_ws/src$ catkin build
  ros@ros-vm:~Workspaces/smb_ws/src$ source ../devel/setup.bash
  ```
  
- Write a [new launch file](https://github.com/Perian-Yan/Introduction-to-ROS/blob/274323fdd8e7d93eb660f9dd99ef3a9acddfd8c8/Exercise%201/smb_common/smb_gazebo/launch/new_world.launch#L5) 
such that
  - load a new world
  - launch the node teleop_twist_keyboard
