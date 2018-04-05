#include <ros/ros.h>
#include <sensor_msgs/Joy.h>
#include <joy_controller/JoyPhid.h>



class TeleopJoyphid
{
public:
  TeleopJoyphid();

private:

  void joyCallback(const sensor_msgs::Joy::ConstPtr& joy);

  ros::NodeHandle nh;
  ros::Publisher cmd_pub;
  ros::Subscriber joy_sub;

  int button_a, button_b, button_x, button_y, reset;
  float vel_1, vel_2, axes, vel_3, axis_tresh;
  bool button_check;

};


TeleopJoyphid::TeleopJoyphid(){


  nh.param("velocity_ab", vel_1, vel_1);
  nh.param("velocity_xy", vel_2, vel_2);
  nh.param("velocity_axis", vel_3, vel_3);
  nh.param("axis_treshold", axis_tresh, axis_tresh);

  cmd_pub = nh.advertise<joy_controller::JoyPhid>("joy_cmd",10);
  joy_sub = nh.subscribe<sensor_msgs::Joy>("joy",10,&TeleopJoyphid::joyCallback,this);


}

void TeleopJoyphid::joyCallback(const sensor_msgs::Joy::ConstPtr& joy)
{

  joy_controller::JoyPhid joyphid;
// Map cpp
  axes = joy->axes[0];
  button_a = joy->buttons[0];
  button_b = joy->buttons[1];
  button_x = joy->buttons[2];
  button_y = joy->buttons[3];
  reset = joy->buttons[6];

  if (axes > axis_tresh) {
    axes = 1.0;
  }
  else if (axes < -1*axis_tresh) {
    axes = -1.0;

  }
  else{
    axes = 0.0;
  }


  if (reset == 1){
    joyphid.vel = 0;
    joyphid.dir = 0;
    button_check = false;
    cmd_pub.publish(joyphid);
  }
  else if (button_a == 1){
    joyphid.vel = vel_1;
    joyphid.dir = 1;
    cmd_pub.publish(joyphid);
    button_check = true;
  }
  else if (button_b == 1){
    joyphid.vel = vel_1;
    joyphid.dir = -1;
    cmd_pub.publish(joyphid);
    button_check = true;
  }
  else if (button_x == 1){
    joyphid.vel = vel_2;
    joyphid.dir = 1;
    cmd_pub.publish(joyphid);
    button_check = true;
  }
  else if (button_y == 1){
    joyphid.vel = vel_2;
    joyphid.dir = -1;
    cmd_pub.publish(joyphid);
    button_check = true;
  }
  else if (axes == 1.0 || axes == -1.0) {
    joyphid.vel = vel_3;
    joyphid.dir = int(axes);
    cmd_pub.publish(joyphid);
    button_check = false;
  }
  else if (axes == 0.0 && button_check == false){
    joyphid.vel = 0.0;
    cmd_pub.publish(joyphid);
  }


}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "teleop_joyphid");
  TeleopJoyphid teleop_joyphid;

  ros::spin();
}
