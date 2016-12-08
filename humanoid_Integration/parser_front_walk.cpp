#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/Int8.h"
#include "readCSV.cpp"
#include "motion/angles_in.h"
#include "motion/angles_out.h"

int flag_data=0;
void callback(const std_msgs::Int8::ConstPtr& msg)
{
  flag_data = msg->data;
  std::cout<<"flag_data_parser"<<flag_data<<std::endl;
}

int main(int argc, char **argv)
{

   int row=240;
   int col=32;//20;//col that we want to read from csv file
   int no_of_cycles=1;
   int frequency=100;

   readCSV file;//object of class readCSV
   std::vector<std::string> data;// vector,data to store returned vector by storeCSV2array
   data=file.storeCSV2array("/home/surabhi/.ros/walk_better.csv",row,col);//by default,the path is taken from .ros
   ros::init(argc, argv, "parser_front_walk");//node name=parser
   ros::NodeHandle n; ros::NodeHandle f; ros::NodeHandle o;
   ros::Subscriber sub_flag = o.subscribe("flag_to_nodes",10,callback); 
   usleep(1000*1000);
   ros::Publisher pub_ang = n.advertise<motion::angles_out>("angle_to_motor", 10);//topic name=angle_to_motor 
   usleep(1000*1000);
   ros::Publisher pub_flag = f.advertise<std_msgs::Int8>("flag_to_dmn", 10);
   usleep(1000*1000);
   std_msgs::Int8 flag;
   motion::angles_in arr;
   motion::angles_out arr1;
   
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
   if (flag_data == 2) //for front walk
    {

    if (k<no_of_cycles)
     {
      ros::Rate loop_rate(frequency);
      for (int i=0; i<row; i++)
      {
       std::cout<<i<<std::endl;
       for (int h=0; h<(col/2); h++)
       {
       arr1.angle_to_motor_out[h] = angle_matrix[i][h];
       } 
       pub_ang.publish(arr1);
       loop_rate.sleep();
      }
      k++; 
      
      flag.data=21; // after completing the reqd no. of cycles
      pub_flag.publish(flag);
      std::cout<<"flag"<<flag<<std::endl;
     }
   } 
 ros::spinOnce();
 }  

return 0;
}


