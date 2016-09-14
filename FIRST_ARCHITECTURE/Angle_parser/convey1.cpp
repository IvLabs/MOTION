#include "ros/ros.h"
#include "std_msgs/String.h"
#include "swayat/angles10.h"
//#include "Herkulex.cpp"
float motor[10];
void chatterCallback(const swayat::angles10::ConstPtr& msg)
{
  for (int num=0; num<10; num++)
   {
     motor[num] = msg->angle2motor[num];
     ROS_INFO("%f",motor[num]);
   }
     ROS_INFO("yoo");
}

int main(int argc, char **argv)
{
  ROS_INFO("in");
  ros::init(argc, argv, "convey1");
  ros::NodeHandle n;

  ros::Subscriber sub = n.subscribe("angle_to_motor", 10, chatterCallback);
  ROS_INFO("subcribed");
  ros::spin();
  return 0;
}
