#include "ros/ros.h"
#include "std_msgs/Int8.h"
#include <iostream>
using namespace std;
int main(int argc, char **argv)
{
  
  ros::init(argc, argv, "flag_node");
  ros::NodeHandle flag_num;
  ros::Publisher flag_pub =          flag_num.advertise<std_msgs::Int8>("flag_topic", 100);

  ros::Rate loop_rate(10);

  int flag = 1;
  while (ros::ok())
  {
    std_msgs::Int8 flag_msg;
    flag_msg.data = flag;
    cout<<flag<<endl;
    flag_pub.publish(flag_msg);

    ros::spinOnce();

    loop_rate.sleep(); break;
  }
 
  return 0;
}
