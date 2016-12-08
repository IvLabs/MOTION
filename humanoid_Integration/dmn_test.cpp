#include "ros/ros.h"
#include "std_msgs/Int8.h"
using namespace std;
int stat=0; int loop;

void callback(const std_msgs::Int8::ConstPtr& msg)
{ 
  stat = msg->data;
  std::cout<<stat<<std::endl; loop=1;
}

int main(int argc, char **argv)
{
   ros::init(argc, argv, "dmn");//node name=dmn
   ros::NodeHandle n; ros::NodeHandle f;
   ros::Subscriber sub_status = n.subscribe("flag_to_dmn",10,callback);
   ros::Publisher pub_flag = f.advertise<std_msgs::Int8>("flag_to_nodes", 10); usleep(1000*1000);
   std_msgs::Int8 flag;
   std_msgs::Int8 status;
   int k=1;

   ros::Rate loop_rate(50);
   while (ros::ok())
   { 
      if(k>0){
        flag.data=1; loop=1; cout<<"if"<<endl;}
      else if(stat>0){
        flag.data=stat;stat=0; cout<<"else"<<endl;}
      k--;
      
      if(loop>0){
        pub_flag.publish(flag); loop--;cout<<"flag"<<endl; cout<<flag<<endl; }

      loop_rate.sleep(); ros::spinOnce();
   }   
return 0;
}


