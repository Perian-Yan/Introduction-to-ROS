#pragma once

#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <string>

#include <sensor_msgs/PointCloud2.h>

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

	ros::Subscriber subscriber_pointcloud;

	void ScanCallback(const sensor_msgs::LaserScan &msg);

	void PointCloudCallback(const sensor_msgs::PointCloud2 &msg);
};

} /* namespace */
