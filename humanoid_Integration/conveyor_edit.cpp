//last edited:30/11/16
#include "ros/ros.h"
#include "motion/angles_out.h"
#include "Herkulex.h"
#include "Herkulex.cpp"

int motor[16]; float bend[16];
void chatterCallback(const motion::angles_out::ConstPtr& msg) //ang_msg object
{
  for (int num=0; num<16; num++)
   {
     motor[num] = msg->angle_to_motor_out[num];
   }
}


int flag_data=1;
void callback(const std_msgs::Int8::ConstPtr& msg)
{
  flag_data = msg->data;
  //std::cout<<"flag_data_parser"<<flag_data<<std::endl;
}

int k=0;
int once = 0;
int motor_id[16]={3,4, 2, 10, 5, 7,9, 12, 8,1,11,6,14,17,18,15};
float bend1[16]={0,-5,25.192,-49.655,-24.463,-5,0,5,-25.192,49.655,24.463,5,0,0,0,0};
float initial[16]={
0.152905198777,
7.49235474006,
1.9877675841+5,
9.98471,
5.65749235474,
-1.07033639144,
0.152905198777,
4.74006116208,
-6.88073394495-5,
-0.152905198777,
0.152905198777,
0.152905198777

};


int main(int argc, char **argv)
{
 HerkulexClass hc;
 for (int i=0;i<16;i++)
  hc.torqueON(motor_id[i]);
 ros::init(argc, argv, "communicator");
 ros::NodeHandle i;
 ros::Subscriber sub_ang = i.subscribe("angle_to_motor", 10, chatterCallback);
 ros::Subscriber sub_flag = o.subscribe("flag_to_nodes",10,callback); 
 usleep(1000*1000);
 std_msgs::Int8 flag;
/////////////////////////////////////////////////////////// INITIAL

if (flag_data==0)
{ 

for (int h=0;h<16;h++)
{
bend[h]=initial[h]+bend1[h];
std::cout<<bend[h]<<std::endl;
}
    for (int num=0; num<16; num++)
    {
     float a = (bend[num]+150);
    bend[num] = round(21+(a/300)*981);
//std::cout<<"b="<<b<<std::endl;
    }

    if (once==0) 
     {
      //ros::Rate r(1428);
      for (int i=0; i<16; i++)
      {
      // std::cout<<"bend="<<bend[i]<<std::endl;
       hc.moveOne(motor_id[i], bend[i] , 1000 , 2); //motor_id, motor_angles, goal_time(from 0 to 2856ms), led_color(1=green)
       sleep(0.0007);
      }
     sleep(2);
     std::cout<<"done"<<std::endl;
     once++;
     }  
////////////////////////////////////////////////////////////   

 ros::Rate loop_rate(50);
 while (ros::ok())
 {
    ros::spinOnce(); //check for incoming messages
   
  if(motor[1]>100)
   {
     if(k==0)
     {
     double secs =ros::Time::now().toSec();
     ROS_INFO("%f",secs); k++;
     }
     
     ros::Rate r(1428); 
     for (int i=0; i<16; i++)
     {
       hc.moveOne(motor_id[i], motor[i], 50, 2); //motor_id, motor_angles, goal_time(from 0 to 2856ms), led_color(1=green)
       r.sleep();
     }
       
   }
  
  loop_rate.sleep();
 }
 hc.Close();
 }
 return 0;
}


