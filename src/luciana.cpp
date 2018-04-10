#include "ros/ros.h"
#include "std_msgs/Float32.h"
#include "std_msgs/Float64.h"
#include "iostream"
#include "phidgets_project/JoyPhid.h"
class Luciana
{

    public:

        Luciana();

        std_msgs::Float32 value;

        phidgets_project::JoyPhid joyphid;


        std_msgs::Float64 y;
        ros::NodeHandle n;
        ros::Publisher pub;
        ros::Subscriber sub;
        ros::Subscriber sub2;

        float set_dist;
        int count;



        void chatterCallback (const std_msgs::Float32::ConstPtr& msg)
        {
            value = *msg;
              //std::cout <<value.data << "  - else\n";

        }






       void chatterCallbackjoy (const phidgets_project::JoyPhid::ConstPtr& msg)
        {
            y=0.0;


            std_msgs::Float32 joy_vel;
            zero_vel=y.vel;

            joyphid = *msg;
            set_dist=7.5;
            ROS_INFO("[%d]",joyphid.vel);

            joy_vel = joyphid.vel;
            ROS_INFO("[%d]",count);
            if (value.data >= set_dist)
            {
                pub.publish(joy_vel);
                count=1;
                std::cout << "if\n";

            }


            else
            {
                pub.publish(y);
                count=0;
                ROS_INFO("HERE");

            }

       }


};
Luciana::Luciana()
        {

            pub = n.advertise<std_msgs::Float64>("command", 10);
            sub = n.subscribe("obstacle_distance", 1000, &Luciana::chatterCallback, this);
            sub2 = n.subscribe("joy_cmd", 1000, &Luciana::chatterCallbackjoy, this);

        }
int main(int argc, char **argv)
{
  ros::init(argc, argv, "motor_control");
  Luciana l;

  //ros::Rate loop_rate(100);
  ros::spin();
  return 0;
}
