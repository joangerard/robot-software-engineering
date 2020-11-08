
#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <math.h>


int main( int argc, char** argv )
{
  ros::init(argc, argv, "basic_shapes");
  ros::NodeHandle n;
  ros::Rate r(1);
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);


  // Set our initial shape type to be a cube
  uint32_t shape = visualization_msgs::Marker::CUBE;

  ros::Time begin = ros::Time::now();

  while(begin.toSec() == 0) {
    begin = ros::Time::now();
  }

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

    ros::Duration elapsed_time(ros::Time::now()-begin);

    // moving the marker to drop off zone
    if(elapsed_time.toSec() > 5 && elapsed_time.toSec() <= 10) {
	//ROS_INFO("The robot has picked up the object %f.", elapsed_time.toSec());
	marker.action = visualization_msgs::Marker::DELETE;
    }
 
    if(elapsed_time > ros::Duration(10)) {
	//ROS_INFO("The robot has dropped off the object %f.", elapsed_time.toSec());
	marker.pose.position.x = 3.7;
    	marker.pose.position.y = 1.4;
    }

    // Set the scale of the marker -- 1x1x1 here means 1m on a side
    marker.scale.x = 0.3;
    marker.scale.y = 0.3;
    marker.scale.z = 0.3;

    // Set the color -- be sure to set alpha to something non-zero!
    marker.color.r = 0.4f;
    marker.color.g = 0.2f;
    marker.color.b = 0.8f;
    marker.color.a = 1.0;

    marker.lifetime = ros::Duration();

    marker_pub.publish(marker);

    ros::spinOnce();
    
  }
}
