#include "ros/ros.h"
#include "motion/angles_in.h"
#include "Herkulex.h"
#include "std_msgs/Int64.h"
#include "Herkulex.cpp"


int motor;
void chatterCallback(const std_msgs::Int64::ConstPtr& msg) //ang_msg object
{  
     motor = msg->data;
     
}

int main(int argc, char **argv)
{
 HerkulexClass hc;


  hc.torqueON(19);

  
  ros::init(argc, argv, "communicator");
  ros::NodeHandle i;
  //ros::NodeHandle o;
  ros::Subscriber sub_ang = i.subscribe("parse_to_motor", 1000, chatterCallback);
  //ros::Publisher pub_ang = o.advertise<motion::angles_out>("chatter", 1000);
  ros::Rate loop_rate(1);
  while (ros::ok())
  {
    ros::spinOnce(); //check for incoming messages
    //motion::angles_out ang_msg_o;
    
       
       hc.moveOne(19, motor, 100, 1);
     
    //pub_ang.publish(ang_msg_o);
    
    for (int i=0; i<10; i++)
     {
       ROS_INFO("%d",motor);
     }

    loop_rate.sleep();
  }
  return 0;
}
