#include "ros/ros.h"
#include "visualization_msgs/MarkerArray.h"
#include "apriltags/AprilTagDetections.h"

#include <ros/ros.h>
#include <ros/forwards.h>
#include <ros/single_subscriber_publisher.h>
#include <sensor_msgs/Image.h>
#include <image_transport/image_transport.h>
#include <visualization_msgs/Marker.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <cv_bridge/cv_bridge.h>
#include <sstream>
#include "std_msgs/String.h"
#include "geometry_msgs/Pose.h"

#include "std_msgs/String.h"
#include "localization_fira/posi.h"

#include <Eigen/Core>
#include <Eigen/Geometry>

#include <visualization_msgs/MarkerArray.h>
#include "yaml-cpp/yaml.h"
#include <sstream>
#include <fstream>
#include "std_msgs/Int8.h"

int start = 0; int stat=0; int k=1;
float z_threshold; float yaw_threshold; //to be set according to robot behavior
float error_yaw; // allowable yaw error
float z_reference; float yaw_reference;
float z_current; float yaw_current;
int start_back_walk = 0; int start_back_walk = 0;
float tag_endline = 0.3; //distance between april tag and endline(in meters)


void pose_callback(const visualization_msgs::Marker::ConstPtr& marker)
//const apriltags::AprilTagDetections::ConstPtr& detections)
{
  if (start<1){ //&& if ready switch is pressed
    z_reference = marker->pose.position.z; //threshold before start switch(to activate initial_step node) is not pressed
    yaw_reference = marker->pose.orientation.z;
   }
  start++;

  else if (start==1) //&& if start switch is pressed
   {
    z_current=marker->pose.position.z;
    yaw_current=marker->pose.orientation.z;
    if(z_current<tag_endline)
      start_back_walk = 1;
    else
      start_front_walk = 1;
   }
}

}
void status_callback(const std_msgs::Int8::ConstPtr& msg)
{ 
  stat = msg->data; //at a time status is received by one parsernode
  loop=1;
}

void orient(int init_step_f, int left_turn_f, int right_turn_f)
{
        if (yaw_current < abs(yaw_reference - yaw_threshold ))
          flag.data=init_step_f; //take initial_back step
        else if (yaw_current > abs(yaw_reference - yaw_threshold ))
          {
           if (yaw_current > (yaw_reference - yaw_threshold ))//left turn
             flag.data=init_step_f;
           else if (yaw_current < (yaw_reference - yaw_threshold ))//right turn
             flag.data=right_turn_f;
           }
} 

void turn()
{
        if (yaw_current > (yaw_reference - yaw_threshold ))//left turn
             flag.data=3;
        else if (yaw_current < (yaw_reference - yaw_threshold ))//right turn
             flag.data=4;
}

void correct_dev(int walk_back_f, int front_to_back_f)
{
        if (yaw_current < abs(yaw_reference - yaw_threshold ))
          flag.data=walk_back_f,; //continue to walk back
        else if (yaw_current > abs(yaw_reference - yaw_threshold ))
          {
           flag.data = front_to_back_f; //get foot from front_to_back
          }        
}

/////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char **argv)
{
   ros::init(argc, argv, "dmn");//node name=dmn
   ros::NodeHandle n; ros::NodeHandle f; ros::NodeHandle c;

   ros::Subscriber sub_status = n.subscribe("flag_to_dmn",1, status_callback);
   ros::Subscriber sub_pose = c.subscribe("/apriltags/marker", 1, pose_callback);
   ros::Publisher pub_flag = f.advertise<std_msgs::Int8>("flag_to_nodes", 10); usleep(1000*1000);
   std_msgs::Int8 flag;
   std_msgs::Int8 status;
   ros::Rate loop_rate(10);

while (ros::ok())
{
 ros::spinOnce();
 
 if(k>0){ //&& start_switch is pressed
        flag.data=1; //initial 
        loop=1;
     }

if(start_front_walk == 1) 
{

   if (stat==11) //initial_step_complete
     flag.data=2; //initiate front_walk
   else if (stat==21)//walking_steps_complete
     correct_dev(2,6)
   else if (stat==61) //foot at initial position
     turn();
   else if (stat==31 || stat==41)
      orient(1,3,4);
}  

////////////////////////////////////////////////////////////////////////

if(start_back_walk == 1) 
{
  if (stat==21 || stat==11) //one leg in front and other at back
   flag.data = 6; //back to front
  else if (stat==61) //foot at initial position
   flag.data = 7; //back_initial
  else if (stat==71) 
   flag.data = 5; //start back_walk
  else if (stat==51)//walking_steps_complete
     correct_dev(5,8);
  else if (stat==81) //foot at initial position
     turn();
  else if (stat==31 || stat==41)
     orient(7,3,4);
}

////////////////////////////////////////////////////////////////////////
 k--;

 if(loop>0)
       {
        pub_flag.publish(flag); 
        loop--;
       }
   

}
 return 0;
}

  


