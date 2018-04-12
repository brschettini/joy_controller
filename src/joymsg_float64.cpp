#include <ros/ros.h>
#include <sensor_msgs/Joy.h>
#include <joy_controller/Joymsg.h>
#include <std_msgs/Float64.h>


class JoymsgDynamix
{
  public:
    JoymsgDynamix();
  private:

    void joydynaCallback(const joy_controller::Joymsg::ConstPtr& joy);

    ros::NodeHandle node;
    ros::Publisher dynamix_pub;
    ros::Subscriber joymsg_sub;


    float vel, vel_cmd;
    int dir;

};




JoymsgDynamix::JoymsgDynamix()
{

  joymsg_sub = node.subscribe<joy_controller::Joymsg>("joy_cmd",10,&JoymsgDynamix::joydynaCallback,this);
  dynamix_pub = node.advertise<std_msgs::Float64>("pan_controller/command",10);

}

void JoymsgDynamix::joydynaCallback(const joy_controller::Joymsg::ConstPtr& joy_msg)
{
  std_msgs::Float64 cmd_dyna;

  vel = joy_msg->vel;
  dir = joy_msg->dir;

  vel_cmd = vel*dir;

  cmd_dyna.data = vel_cmd;

  dynamix_pub.publish(cmd_dyna);


}



int main(int argc, char** argv)
{
  ros::init(argc,argv, "joymsg_dynamix");

  JoymsgDynamix joymsgdynamix;

  ros::spin();

}
