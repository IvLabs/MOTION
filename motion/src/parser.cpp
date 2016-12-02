//date:1/12/16
//written by-sakshi
//receives data from csv file and published on a node with custom msg int64[10]
#include "ros/ros.h"
#include "std_msgs/String.h"
#include "readCSV.cpp"
#include "motion/angles_in.h"
#include "motion/angles_out.h"

int main(int argc, char **argv)
{
   readCSV file;//object of class readCSV
   std::vector<std::string> data;// vector,data to store returned vector by storeCSV2array
   int row=120;
   int col=32;//20;//col that we want to read from csv file
 
   data=file.storeCSV2array("/home/ivlabs/.ros/tap_parser_new.csv",row,col);//by default,the path is taken from .ros
   ros::init(argc, argv, "parser");//node name=angle_parser
   ros::NodeHandle n;
   ros::Publisher pub_ang = n.advertise<motion::angles_out>("angle_to_motor", 10);//topic name=angle_to_mo
   motion::angles_in arr;
   motion::angles_out arr1;
   int no_of_cycles=60;
   int k=0;
   float angle_matrix[row][col];
   ros::Time begin = ros::Time::now();
   for(int i=0;i<row;i++)
        { 
          std::vector<float> vect;
          std::stringstream ss(data.at(i));
          float m;
          while (ss >> m)
           {
             vect.push_back(m);
             if (ss.peek() == ',')
                ss.ignore();
           }
          for (int h=0; h<(col/2); h++)
           { 
            vect.at(h) = vect.at(h)+vect.at(h+(col/2));
            angle_matrix[i][h] = vect.at(h); 
            angle_matrix[i][h] = round(((angle_matrix[i][h]+150)/300)*981+21);
           }
        }


   while (ros::ok())
   {
    
    if (k<no_of_cycles)
     {
      ros::Rate loop_rate(100);
      for (int i=0; i<row; i++)
      {
       //std::cout<<i<<std::endl;
       for (int h=0; h<(col/2); h++)
       {
       arr1.angle_to_motor_out[h] = angle_matrix[i][h];
       } 
       pub_ang.publish(arr1);
       loop_rate.sleep();
      }
      
      ros::spinOnce();
      //std::cout<<k<<std::endl;
      k++; 
     }
   }   

return 0;
}

