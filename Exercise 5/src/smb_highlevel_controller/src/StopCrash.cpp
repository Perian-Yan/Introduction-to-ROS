#include <ros/ros.h>
#include "smb_highlevel_controller/SmbHighlevelController.hpp"
#include <sensor_msgs/Imu.h>

void ObstacleCallback(const sensor_msgs::Imu &msg)
{
  
  float a_x = msg.linear_acceleration.x;

  ros::NodeHandle nh("~");
  std::string service_name = "/stop_smb";
  ros::ServiceClient client = nh.serviceClient<std_srvs::SetBool>(service_name);
  
  std_srvs::SetBool stop;
  if(abs(a_x)>1.5)
  {
    stop.request.data = 1;
    if (client.call(stop))
      ROS_INFO_STREAM(stop.response.message);
  }
}

int main(int argc, char** argv) {
  ros::init(argc, argv, "stop_crash");
  ros::NodeHandle nh("~");
 
  ros::Subscriber subscriber_imu = nh.subscribe("/imu0", 10, ObstacleCallback);

  ros::spin();
  return 0;
}
