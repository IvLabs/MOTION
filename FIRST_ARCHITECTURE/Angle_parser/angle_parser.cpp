//date:12/9/16
//written by-sakshi
//receives data from csv file and published on a node with custom msg int64[10]
#include "ros/ros.h"
#include "std_msgs/String.h"
#include <readCSV.cpp>
#include "swayat/angles10.h"

int main(int argc, char **argv)
{
   readCSV file;//object of class readCSV
   std::vector<std::string> data;// vector,int to store returned vector by storeCSV2array
   int row=20;//rows that we want to read from csv file
   int col=3;//col that we want to read from csv file

   data=file.storeCSV2array("/home/sakshi/.ros/try1.csv",row,col);//by default,the path is taken from .ros


   ros::init(argc, argv, "angle_parser");//node name=angle_parser
   ros::NodeHandle n;
   ros::Publisher ang_pub = n.advertise<swayat::angles10>("angle_to_motor", 10);//topic name=angle_to_mo

   std::cout << data[1];
   swayat::angles10 arr;
   int no_of_cycles=1;
   int k=0;
   while (ros::ok())
   {
 //  if (k<no_of_cycles)
    // {
      for(int i=0;i<row;i++)
        { 
          ros::Rate loop_rate(1);
          std::vector<int> vect;
          std::stringstream ss(data.at(i));
          int m;
          while (ss >> m)
           {
             vect.push_back(m);
             if (ss.peek() == ',')
                ss.ignore();
           }

          for (int h=0; h< vect.size();h++)
             arr.angle2motor[h]=vect.at(h) ; 
          ang_pub.publish(arr);
          ROS_INFO("PUBLISHED");
          int j=arr.angle2motor[3];//for verifying
          ROS_INFO("%d",j);
 
          
          loop_rate.sleep();
        }
     ros::spinOnce();
     k++;   
  //   }    
   }
return 0;
}
