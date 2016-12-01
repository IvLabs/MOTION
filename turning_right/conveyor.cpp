//last edited:30/11/16
#include "ros/ros.h"
#include "motion/angles_out.h"
#include "Herkulex.h"
#include "Herkulex.cpp"

int motor[16];
void chatterCallback(const motion::angles_out::ConstPtr& msg) //ang_msg object
{
  for (int num=0; num<16; num++)
   {
     motor[num] = msg->angle_to_motor_out[num];
    // if (num>10)
    // ROS_INFO("%d",motor[num]);
   }
}
////////////////////////////!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
int k=0;
int once = 0;
//rt_hip_yaw//rt_h_roll//rt_h_pt//rt_k_pt//rt_ank_pt//rt_ank_roll//lf_hip_yaw//lf_h_roll//lf_h_pt//lf_k_pt//lf_ank_pt//lf_ank_roll//rt_hand_pt//lf_hand_pt//head_yaw//head_pitch
int motor_id[16]={3,4, 2, 10, 5, 7,9, 12, 8,1,11,6,14,17,18,15};

float bend1[16]=
{0,//0 or 4 rhy
-4,//0 rhr  
22.5,//0 rhp  // 5 
-45,//0 rkp
-22.5,//0 rap
-5,//0 rar
0, //0
5, //5
-27.5, //-5   //-10
45, //0
22.5, //0
7.3, //2.3
0,
0,
0,
0
};


//float bend1[16]={0, 0, 5, 0, 0, 0, 0, 5, -10, 0, 0, 2.3, 0, 0, 0, 0};
float initial[16]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
float max[16]={-6.6516,34.787036414,-69.5740728286,-34.7870364143,-6.6516,0,-22.5,45,22.5,-6.6516,0,0,0,0,0,0};
float bend[16];


/////////////////


int main(int argc, char **argv)
{
 HerkulexClass hc;
  for (int i=0;i<16;i++)
  hc.torqueON(motor_id[i]);
 ros::init(argc, argv, "communicator");
 ros::NodeHandle i;
 ros::Subscriber sub_ang = i.subscribe("angle_to_motor", 10, chatterCallback);

/////////////////////////////////////////////////////////// INITIAL
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
       hc.moveOne(motor_id[i], bend[i] , 1000 , 1); //motor_id, motor_angles, goal_time(from 0 to 2856ms), led_color(1=green)
       sleep(0.0007);
      }
     sleep(2);
     std::cout<<"done"<<std::endl;
     once++;
     }  
////////////////////////////////////////////////////////////   

 ros::Rate loop_rate(75);
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
 std::cout<<"closed";
 hc.Close();
 return 0;
}

