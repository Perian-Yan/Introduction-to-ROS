#include <smb_highlevel_controller/SmbHighlevelController.hpp>

namespace smb_highlevel_controller {

SmbHighlevelController::SmbHighlevelController(ros::NodeHandle& nodeHandle) :
  
  nodeHandle_(nodeHandle) 
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
  
  if(!nodeHandle_.getParam("controller_gain/linear", kp_x)) 
    {
      ROS_ERROR("Could not find the controller gain parameter!");
    }
  if(!nodeHandle_.getParam("controller_gain/angular", kp_theta)) 
    {
      ROS_ERROR("Could not find the controller gain parameter!");
    }
  subscriber_ = nodeHandle_.subscribe(topic, queue_size, &SmbHighlevelController::ScanCallback, this);
  
  subscriber_pointcloud = nodeHandle_.subscribe("/rslidar_points", 10, &SmbHighlevelController::PointCloudCallback, this);

  publisher_twist = nodeHandle_.advertise<geometry_msgs::Twist>("/cmd_vel",10);

  publisher_marker = nodeHandle_.advertise<visualization_msgs::Marker>("/visualization_marker", 10);
  
  publisher_marker2 = nodeHandle_.advertise<visualization_msgs::Marker>("/visualization_marker", 10);
}


void SmbHighlevelController::ScanCallback(const sensor_msgs::LaserScan &msg)
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
  // theta is the angular between car's x-axis and the pillar
  float x = msg.ranges[i_min];
  float theta = msg.angle_min + i_min*msg.angle_increment-(msg.angle_min+msg.angle_max)/2;
  
  // TA: A more practical way is averaging the distance and angle: 
  // int j;
  // double sum_dist = 0;
  // double sum_angle = 0;
  // int count = 0;
  // for (j=0; j<size; j++)
  // {
  //   if(msg.ranges[j] > msg.range_min && msg.ranges[j] < msg.range_max)
  //     {
  //       sum_dist += msg.ranges[j];
  //       sum_angle += j*msg.angle_increment;
  //       count++;
  //     }
  // } 
  // x = sum_dist / count;
  // theta = msg.angle_min + sum_angle/count - (msg.angle_min+msg.angle_max)/2;
  // ---------------------------------------------------------------------
  
  geometry_msgs::Twist ctrl;
  ctrl.angular.z = theta * kp_theta;
  ctrl.linear.x = x * kp_x; //0.5
  if(x < 5)
    ctrl.linear.x = 0.5;
  ROS_INFO_STREAM("The distance is " << x << 
                    ". The angular is " << theta << ".");
  publisher_twist.publish(ctrl);

  visualization_msgs::Marker marker;
    marker.header.frame_id = "rslidar";
    marker.header.stamp = ros::Time();
    marker.ns = "ns";
    marker.id = 0;
    marker.type = visualization_msgs::Marker::SPHERE;
    marker.action = visualization_msgs::Marker::ADD;
    marker.pose.position.x = x*cos(theta);
    marker.pose.position.y = x*sin(theta);
    marker.pose.position.z = 0.0;         // x,y,and z are in the rslidar frame
    marker.pose.orientation.x = 0.0;
    marker.pose.orientation.y = 0.0;
    marker.pose.orientation.z = 0.0;
    marker.pose.orientation.w = 1.0;
    marker.scale.x = 0.5;
    marker.scale.y = 0.5;
    marker.scale.z = 0.5;
    marker.color.a = 1.0; // Don't forget to set the alpha!
    marker.color.r = 0.0;
    marker.color.g = 1.0;
    marker.color.b = 0.0;
    publisher_marker.publish(marker);


  // TF listener: transform extracted point from laser frame to odom frame
  try{
    listener.lookupTransform("odom","rslidar",ros::Time(0), transform);
  } catch(tf::TransformException ex){
    ROS_ERROR("%s", ex.what());
    ros::Duration(1.0).sleep();
  }

  float x_car = transform.getOrigin().x();
  float y_car = transform.getOrigin().y();
  float z_car = transform.getOrigin().z();
  float angle_car = atan2(y_car, x_car);
  
  visualization_msgs::Marker marker2;
    marker2.header.frame_id = "odom";
    marker2.header.stamp = ros::Time();
    marker2.ns = "ns";
    marker2.id = 1;  // choose a different id in order to visualize two markers
    marker2.type = visualization_msgs::Marker::CUBE;
    marker2.action = visualization_msgs::Marker::ADD;
    marker2.pose.position.x = x_car + x*cos(angle_car + theta);
    marker2.pose.position.y = y_car + x*sin(angle_car + theta);
    marker2.pose.position.z = z_car;         // x,y,and z are in the rslidar frame
    marker2.pose.orientation.x = 0.0;
    marker2.pose.orientation.y = 0.0;
    marker2.pose.orientation.z = 0.0;
    marker2.pose.orientation.w = 1.0;
    marker2.scale.x = 0.4;
    marker2.scale.y = 0.4;
    marker2.scale.z = 0.4;
    marker2.color.a = 1.0; // Don't forget to set the alpha!
    marker2.color.r = 0.0;
    marker2.color.g = 0.0;
    marker2.color.b = 1.0;
    publisher_marker2.publish(marker2);

    ROS_INFO("Marker in odom frame: %f, %f." , marker2.pose.position.x, marker2.pose.position.y);

}

void SmbHighlevelController::PointCloudCallback(const sensor_msgs::PointCloud2 &msg)
{
  int point_step = msg.point_step;
  int data = msg.data.size();
  // ROS_INFO("The number of points is %d", data / point_step); 

}

SmbHighlevelController::~SmbHighlevelController()
{
}

} /* namespace */