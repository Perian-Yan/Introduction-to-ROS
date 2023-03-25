#pragma once

#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <string>

#include <sensor_msgs/PointCloud2.h> // exercise 2 optional

#include<geometry_msgs/Twist.h> // exercise 3
#include<visualization_msgs/Marker.h>
#include<math.h>
#include<tf/transform_listener.h>

#include<std_srvs/SetBool.h> // exercise 5

namespace smb_highlevel_controller {

/*!
 * Class containing the Husky Highlevel Controller
 */
class SmbHighlevelController {
public:
	/*!
	 * Constructor.
	 */
	SmbHighlevelController(ros::NodeHandle& nodeHandle);

	/*!
	 * Destructor.
	 */
	virtual ~SmbHighlevelController();
	
private:
	ros::NodeHandle nodeHandle_;
	ros::Subscriber subscriber_;
	void ScanCallback(const sensor_msgs::LaserScan &msg);
	
	// Exercise 2 opitional
	ros::Subscriber subscriber_pointcloud;
	void PointCloudCallback(const sensor_msgs::PointCloud2 &msg);

	// Exercise 3
	ros::Publisher publisher_twist;
	ros::Publisher publisher_marker;

	float kp_x; // P-controller gain
  	float kp_theta;
	
	ros::Publisher publisher_marker2; // Exercise 3 optional

	tf::TransformListener listener;
	tf::StampedTransform transform;

	// Exercise 5
	bool stop;  // define a flag: 1 for stop the robot, 0 for start
	std::string service_name;
	ros::ServiceServer service;
	bool StopCallback(std_srvs::SetBool::Request &request, 
				  std_srvs::SetBool::Response &response);
};

} /* namespace */