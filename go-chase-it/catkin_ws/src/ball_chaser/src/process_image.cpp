#include "ros/ros.h"
#include "ball_chaser/DriveToTarget.h"
#include <sensor_msgs/Image.h>
#include <string>

using namespace std;

// Define a global client that can request services
ros::ServiceClient client;
string FORWARD = "forward";
string LEFT = "left";
string RIGHT = "right";
string STOP = "stop";
string last_movement = "";

// This function calls the command_robot service to drive the robot in the specified direction
void drive_robot(float lin_x, float ang_z)
{
    // TODO: Request a service and pass the velocities to it to drive the robot
    ball_chaser::DriveToTarget srv;
    srv.request.linear_x = lin_x;
    srv.request.angular_z = ang_z;
    
    // Call the safe_move service and pass the requested direction
    if (!client.call(srv))
        ROS_ERROR("Failed to call service command_robot");
}

// This callback function continuously executes and reads the image data
void process_image_callback(const sensor_msgs::Image img)
{

    int white_pixel = 255;
    int white_pixel_pos = -1;
    int partition = (int)img.step/3;
    int diff = 100;

    // Loop through each pixel in the image and check if its equal to the first one
    for (int i = 0; i < img.height * img.step; i=i+3) {
        if (img.data[i] == white_pixel && img.data[i+1] == white_pixel && img.data[i+2] == white_pixel) {
            white_pixel_pos = i % img.step;
            break;
        }
    }
    
    // ball is not in the image
    if (white_pixel_pos == -1 && last_movement.compare(STOP) != 0) {
        last_movement = STOP;
        ROS_INFO_STREAM("Stop the robot...");
        drive_robot(0.0, 0.0);
    }
    // ball is in the left
    else if (white_pixel_pos >= 0 && white_pixel_pos <= partition - diff
             && last_movement.compare(LEFT) != 0) {
        last_movement = LEFT;
        ROS_INFO_STREAM("Moving the robot to the left...");
        drive_robot(0.0, 0.3);
    }
    // ball is in the center
    else if (white_pixel_pos > partition - diff && white_pixel_pos <= partition*2 + diff && last_movement.compare(FORWARD) != 0) {
        last_movement = FORWARD;
        ROS_INFO_STREAM("Moving the robot forward...");
        drive_robot(0.3, 0.0);
    }
    // ball is in the right
    else if (white_pixel_pos > partition*2 + diff && white_pixel_pos <= partition*3 && last_movement.compare(RIGHT) != 0) {
        last_movement = RIGHT;
        ROS_INFO_STREAM("Moving the robot to the right...");
        drive_robot(0.0, -0.3);
    }
}

int main(int argc, char** argv)
{
    // Initialize the process_image node and create a handle to it
    ros::init(argc, argv, "process_image");
    ros::NodeHandle n;

    // Define a client service capable of requesting services from command_robot
    client = n.serviceClient<ball_chaser::DriveToTarget>("/ball_chaser/command_robot");

    // Subscribe to /camera/rgb/image_raw topic to read the image data inside the process_image_callback function
    ros::Subscriber sub1 = n.subscribe("/camera/rgb/image_raw", 10, process_image_callback);

    // Handle ROS communication events
    ros::spin();

    return 0;
}
