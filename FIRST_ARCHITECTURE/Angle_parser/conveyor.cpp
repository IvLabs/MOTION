#include "ros/ros.h"
#include "motion/angles_in.h"
#include "herkulex.cpp"

int motor[10];
void chatterCallback(const motion::angles_in::ConstPtr& msg) //ang_msg object
{
  for (int num=0; num<10; num++)
   {
     motor[num] = msg->angle_to_motor_in[num];
   }
}
/////////////////

int motor_id[10]={4, 2, 10, 5, 7, 12, 8, 1, 11, 6};
for (int i=0;i<10;i++)
  HerkulexClass::torqueON(motor_id[i]);

/////////////////

int main(int argc, char **argv)
{
  
  ros::init(argc, argv, "communicator");
  ros::NodeHandle i;
  //ros::NodeHandle o;
  ros::Subscriber sub_ang = i.subscribe("parse_to_motor", 1000, chatterCallback);
  //ros::Publisher pub_ang = o.advertise<motion::angles_out>("chatter", 1000);
  ros::Rate loop_rate(33);
  while (ros::ok())
  {
    ros::spinOnce(); //check for incoming messages
    //motion::angles_out ang_msg_o;
    
    for (int i=0; i<10; i++)
     {
       HerkulexClass::moveOne(motor_id[i], motor[i], 22, 1);
     }
    //pub_ang.publish(ang_msg_o);
    
    for (int i=0; i<10; i++)
     {
       ROS_INFO("%f",motor[i]);
     }

    loop_rate.sleep();
  }
  return 0;
}
