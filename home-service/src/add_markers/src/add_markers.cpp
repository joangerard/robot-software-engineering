
#include <nav_msgs/Odometry.h>
#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <math.h>

bool picked_up = false;
bool drop_off = false;


// Define callback function for odometry
void odometry_cb(const nav_msgs::Odometry::ConstPtr& msg) 
{
	float robot_pose_x = msg->pose.pose.position.x;
	float robot_pose_y = msg->pose.pose.position.y;

	float pickup_dis = sqrt(pow((-3.5 - robot_pose_x), 2) + pow((1.3 - robot_pose_y), 2));
	float dropoff_dis = sqrt(pow((3.7 - robot_pose_x), 2) + pow((1.4 - robot_pose_y), 2));
	//ROS_INFO("x: %f, y: %f", robot_pose_x, robot_pose_y);
	if(pickup_dis < 0.3 && !picked_up) {
		ROS_INFO("Robot picked up the object");
		picked_up = true;
		drop_off = false;
	}

	if (dropoff_dis < 0.6 && !drop_off) {
		ROS_INFO("Robot drop off the object");
		picked_up = false;
		drop_off = true;
	}
	
}

int main( int argc, char** argv )
{
  ros::init(argc, argv, "basic_shapes");
  ros::NodeHandle n;
  ros::Rate r(1);
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);

  // Subscribe to odometry values
  ros::Subscriber odometry_sub = n.subscribe("odom", 1000, odometry_cb);


  // Set our initial shape type to be a cube
  uint32_t shape = visualization_msgs::Marker::CUBE;
  ROS_INFO("test");
	

  while (ros::ok())
  {
    visualization_msgs::Marker marker;
    // Set the frame ID and timestamp.  See the TF tutorials for information on these.
    marker.header.frame_id = "/map";
    marker.header.stamp = ros::Time::now();
   
    

    // Set the namespace and id for this marker.  This serves to create a unique ID
    // Any marker sent with the same namespace and id will overwrite the old one
    marker.ns = "basic_shapes";
    marker.id = 0;


    // Set the marker type.  Initially this is CUBE, and cycles between that and SPHERE, ARROW, and CYLINDER
    marker.type = shape;


    // Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
    marker.action = visualization_msgs::Marker::ADD;

    // Set the pose of the marker.  This is a full 6DOF pose relative to the frame/time specified in the header
    marker.pose.position.x = -3.5;
    marker.pose.position.y = 1;
    marker.pose.position.z = 0;
    marker.pose.orientation.x = 0.0;
    marker.pose.orientation.y = 0.0;
    marker.pose.orientation.z = 0.0;
    marker.pose.orientation.w = 1.0;

    // moving the marker to drop off zone
    if(picked_up) {
	marker.action = visualization_msgs::Marker::DELETE;
    }
 
    if(drop_off) {
	marker.pose.position.x = 3.7;
    	marker.pose.position.y = 1.4;
    }

    // Set the scale of the marker -- 1x1x1 here means 1m on a side
    marker.scale.x = 0.3;
    marker.scale.y = 0.3;
    marker.scale.z = 0.3;

    // Set the color -- be sure to set alpha to something non-zero!
    marker.color.r = 0.4f;
    marker.color.g = 0.8f;
    marker.color.b = 0.8f;
    marker.color.a = 1.0;

    marker.lifetime = ros::Duration();

    // Publish the marker
    while (marker_pub.getNumSubscribers() < 1)
    {
      if (!ros::ok())
      {
        return 0;
      }
      ROS_WARN_ONCE("Please create a subscriber to the marker");
      sleep(1);
    }
    marker_pub.publish(marker);

    ros::spinOnce();
    
  }
}
