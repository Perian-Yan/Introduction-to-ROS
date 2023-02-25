#include <smb_highlevel_controller/SmbHighlevelController.hpp>

namespace smb_highlevel_controller {

SmbHighlevelController::SmbHighlevelController(ros::NodeHandle& nodeHandle) :
  
  nodeHandle_(nodeHandle) // nodeHandle_ = nodeHandle;
{
  std::string topic;
  int queue_size;
  
  if(!nodeHandle_.getParam("topic", topic)) 
    {
      ROS_ERROR("Could not find the topic parameter!");
    }
  

  if(!nodeHandle_.getParam("queue_size", queue_size)) 
    {
      ROS_ERROR("Could not find the queue_size parameter!");
    }
    
  subscriber_ = nodeHandle_.subscribe(topic, queue_size, &SmbHighlevelController::ScanCallback, this);
  
  subscriber_pointcloud = nodeHandle_.subscribe("/rslidar_points", 10, &SmbHighlevelController::PointCloudCallback, this);

}

void SmbHighlevelController::ScanCallback(const sensor_msgs::LaserScan &msg)
{
  
  int num = msg.ranges.size();
  float min = msg.range_max;
  int i;

  for (i = 0; i < num; i++)
  {
    if(msg.ranges[i] > msg.range_min && msg.ranges[i] < min)
      min = msg.ranges[i];
  }
  ROS_INFO_STREAM("The smallest distance: " << min << " (m)");

}

void SmbHighlevelController::PointCloudCallback(const sensor_msgs::PointCloud2 &msg)
{
  int point_step = msg.point_step;
  int data = msg.data.size();
  ROS_INFO("The number of points is %d", data / point_step); 
}

SmbHighlevelController::~SmbHighlevelController()
{
}

} /* namespace */
