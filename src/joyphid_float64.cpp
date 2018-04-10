#include <ros/ros.h>
#include <sensor_msgs/Joy.h>
#include <joy_controller/JoyPhid.h>
#include <std_msgs/Float64.h>


class JoyphidDynamix
{
  public:
    JoyphidDynamix();
  private:

    void joydynaCallback(const joy_controller::JoyPhid::ConstPtr& joy);

    ros::NodeHandle node;
    ros::Publisher dynamix_pub;
    ros::Subscriber joyphid_sub;

    float vel, vel_cmd;
    int dir;

};




JoyphidDynamix::JoyphidDynamix()
{

  joyphid_sub = node.subscribe<joy_controller::JoyPhid>("joy_cmd",10,&JoyphidDynamix::joydynaCallback,this);
  dynamix_pub = node.advertise<std_msgs::Float64>("pan_controller/command",10);

}

void JoyphidDynamix::joydynaCallback(const joy_controller::JoyPhid::ConstPtr& j_phid)
{
  std_msgs::Float64 cmd_dyna;

  vel = j_phid->vel;
  dir = j_phid->dir;

  vel_cmd = vel*dir;

  cmd_dyna.data = vel_cmd;

  dynamix_pub.publish(cmd_dyna);


}



int main(int argc, char** argv)
{
  ros::init(argc,argv, "joyphid_dynamix");

  JoyphidDynamix joyphidynamix;

  ros::spin();

}
