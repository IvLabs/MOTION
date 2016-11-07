#include "ros/ros.h"
#include "std_msgs/Int8.h"

#include <sstream>
#include <SerialPort.h>
#include <iostream>
#include <sys/select.h>
#include <sys/time.h>
#include <unistd.h>

int main(int argc, char **argv)
{
  SerialPort s("/dev/ttyACM0");
  SerialPort::BaudRate b;
  b=s.BAUD_9600;
  s.Open(b);
  ros::init(argc, argv, "global_planner");
  ros::NodeHandle n;
  ros::Publisher chatter_pub = n.advertise<std_msgs::Int8>("Tiva", 1000);
  ros::Rate loop_rate(10);

  int count = 0;
  while (ros::ok())
  {
    std_msgs::Int8 msg;
    msg.data =s.ReadByte();
    ROS_INFO("%d", msg.data);
    chatter_pub.publish(msg);

    ros::spinOnce();

    loop_rate.sleep();
    ++count;
  }


  return 0;
}
