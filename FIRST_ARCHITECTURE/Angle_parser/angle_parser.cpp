#include "ros/ros.h"
#include "std_msgs/String.h"
#include <readCSV.cpp>
#include <fstream>
#include <sstream>
#include "swayat/array10.h"


int main(int argc, char **argv)
{
   readCSV file;//object of class readCSV
   vect2d data;//2d vector,int
   int row=3;
   int col=3;
   data=file.storeCSV2array("/home/sakshi/.ros/swayat.csv",row,col);//by default,the path is taken from .ros
 
   ros::init(argc, argv, "angle_parser");
   ros::NodeHandle n;
   ros::Publisher ang_pub = n.advertise<swayat::array10>("custom_msg", 10);
   ros::Rate loop_rate(1);
    
 
  int count = 0;
  swayat::array10 arr;
  while (ros::ok())
  {
   

    for(int i=0;i<3;i++)
    { 
      
      for(int j=0;j<3;j++)
       {
        arr.Array[j]=data[i][j];
       }
    ang_pub.publish(arr);
    }
   
    ros::spinOnce();
    loop_rate.sleep();
    
  }
  return 0;
}
