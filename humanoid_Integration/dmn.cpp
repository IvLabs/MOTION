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
   }
}

}
void status_callback(const std_msgs::Int8::ConstPtr& msg)
{ 
  stat = msg->data; //at a time status is received by one parsernode
  loop=1;
}

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

{
 else if (stat==11) //initial_step_complete
     {
        flag.data=2; //initiate front_walk
        stat=0; 
     }
 else if (stat==21)//walking_steps_complete
     {
        if (yaw_current < abs(yaw_reference - yaw_threshold ))
          flag.data=2; //continue to walk front
        else if (yaw_current > abs(yaw_reference - yaw_threshold ))
          {
           flag.data = 6; //get foot from back to front
          }        
     }
  else if (stat==61) //foot at initial position
     {
        if (yaw_current > (yaw_reference - yaw_threshold ))//left turn
             flag.data=3;
        else if (yaw_current < (yaw_reference - yaw_threshold ))//right turn
             flag.data=4;
      }
  else if (stat==31 || stat==41)
     {
        if (yaw_current < abs(yaw_reference - yaw_threshold ))
          flag.data=1; //take initial step
        else if (yaw_current > abs(yaw_reference - yaw_threshold ))
          {
           if (yaw_current > (yaw_reference - yaw_threshold ))//left turn
             flag.data=3;
           else if (yaw_current < (yaw_reference - yaw_threshold ))//right turn
             flag.data=4;
           }
     }

}
  
 else if(stat==51) //initial_step_complete
     {
        flag.data=5; //initiate front_walk
        stat=0; 
     }
 
 k--;

 if(loop>0){
        pub_flag.publish(flag); 
        loop--;
           }
   

}
 return 0;
}

  


