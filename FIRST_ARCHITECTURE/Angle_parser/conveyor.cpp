#include "ros/ros.h"
#include "motion/angles10.h"
#include "Herkulex.h"
#include "Herkulex.cpp"

int motor[10];
void chatterCallback(const motion::angles10::ConstPtr& msg) //ang_msg object
{
  for (int num=0; num<10; num++)
   {
     motor[num] = msg->angle2motor[num];
   }
}
/////////////////


int main(int argc, char **argv)
{
  HerkulexClass hc;
  int motor_id[10]={4, 2, 10, 5, 7, 12, 8, 1, 11, 6};
  for (int i=0;i<10;i++)
  hc.torqueON(motor_id[i]);

  ros::init(argc, argv, "communicator");
  ros::NodeHandle i;

  ros::Subscriber sub_ang = i.subscribe("parse_to_motor", 10, chatterCallback);
  
  ros::Rate loop_rate(33);
  while (ros::ok())
  {
    ros::spinOnce(); //check for incoming messages
    //motion::angles_out ang_msg_o;
    
    for (int i=0; i<10; i++)
     {
       hc.moveOne(motor_id[i], motor[i], 22, 1);
     }
    //pub_ang.publish(ang_msg_o);
    
    for (int i=0; i<10; i++)
     {
       ROS_INFO("%d",motor[i]);
     }

    loop_rate.sleep();
  }
  return 0;
}
