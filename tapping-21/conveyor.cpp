
#include "ros/ros.h"
#include "motion/angles_out.h"
#include "Herkulex.h"
#include "Herkulex.cpp"

int motor[10];
void chatterCallback(const motion::angles_out::ConstPtr& msg) //ang_msg object
{
  for (int num=0; num<10; num++)
   {
     motor[num] = msg->angle_to_motor_out[num];
     ROS_INFO("%d",motor[num]);
   }
}
////////////////////////////!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
int k=0;
int once = 0;
int motor_id[10]={4, 2, 10, 5, 7, 12, 8, 1,11,6};
 //int stand[10]={512,554,478,485,512,512,478,544,537,512};
 //int bend[10]={486,590,393,458,538,514,437,631,752,405};
//int bend[10]={-16,25,-26,-2,3,7,-13,29,16,-41}



int initial[10]={0,0,0,0,0,0,0,0,0,0};
int bend1[10]={-3,20.5,-41,-20.5,-3,3,-22.5,45,22.5,3};	//l_hip_pitch-2,l_ankle_pitch-2

int bend[10];



//int bend[10]={482,580,413,485,495,527,472,616};//,513};

/////////////////


int main(int argc, char **argv)
{
 HerkulexClass hc;
  for (int i=0;i<10;i++)
  hc.torqueON(motor_id[i]);
 ros::init(argc, argv, "communicator");
 ros::NodeHandle i;
 ros::Subscriber sub_ang = i.subscribe("angle_to_motor", 10, chatterCallback);

/////////////////////////////////////////////////////////// INITIAL
for (int h=0;h<10;h++)
{
bend[h]=initial[h]+bend1[h];

}
    for (int num=0; num<10; num++)
    {
     float a = (bend[num]+150);
    bend[num] = round(21+(a/300)*981);
//std::cout<<"b="<<b<<std::endl;
    }

    if (once==0) 
     {
      //ros::Rate r(1428);
      for (int i=0; i<10; i++)
      {
       std::cout<<"bend="<<bend[i]<<std::endl;
       hc.moveOne(motor_id[i], bend[i] , 1000 , 1); //motor_id, motor_angles, goal_time(from 0 to 2856ms), led_color(1=green)
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
     for (int i=0; i<10; i++)
     {
       hc.moveOne(motor_id[i], motor[i], 35, 2); //motor_id, motor_angles, goal_time(from 0 to 2856ms), led_color(1=green)
       r.sleep();
     }
       
   }
  
  loop_rate.sleep();
 }
 std::cout<<"closed";
 hc.Close();
 return 0;
}

