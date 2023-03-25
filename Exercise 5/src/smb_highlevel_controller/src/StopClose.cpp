#include <ros/ros.h>
#include "smb_highlevel_controller/SmbHighlevelController.hpp"


void ObstacleCallback(const sensor_msgs::LaserScan &msg)
{
  
  int size = msg.ranges.size();
  float min = msg.range_max;
  int i;
  int i_min;
  for (i = 0; i < size; i++)
  {
    if(msg.ranges[i] > msg.range_min && msg.ranges[i] < min)
      {
        min = msg.ranges[i];
        i_min = i;
      }
  }
  //ROS_INFO_STREAM("The smallest distance: " << min << " (m)");
   
  // x is the shortest distance from car to the pillar
  // theta is the angle between car's x-axis and the pillar
  float x = msg.ranges[i_min];
  float theta = msg.angle_min + i_min*msg.angle_increment-(msg.angle_min+msg.angle_max)/2;
  
  ros::NodeHandle nh("~");
  // std::string service_name;
  // if(!nh.getParam("service_name", service_name)) 
  //   {
  //     ROS_ERROR("Could not find the service name!");
  //   }
  std::string service_name = "/stop_smb";
  ros::ServiceClient client = nh.serviceClient<std_srvs::SetBool>(service_name);
  
  std_srvs::SetBool stop;
  if(x<4)
  {
    stop.request.data = 1;
    if (client.call(stop))
      ROS_INFO_STREAM(stop.response.message);
  }
}


int main(int argc, char** argv) {
  ros::init(argc, argv, "stop_close");
  ros::NodeHandle nh("~");
 
  ros::Subscriber subscriber_scan = nh.subscribe("/scan", 10, ObstacleCallback);

  ros::spin();
  return 0;
}




