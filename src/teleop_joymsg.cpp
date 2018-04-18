#include <ros/ros.h>
#include <sensor_msgs/Joy.h>
#include <joy_controller/Joymsg.h>

class TeleopJoyMsg
{

public:
  TeleopJoyMsg();

private:

  void joyCallback(const sensor_msgs::Joy::ConstPtr& joy);

  ros::NodeHandle nh;
  ros::Publisher cmd_pub;
  ros::Subscriber joy_sub;

  int button_a, button_b, button_x, button_y, reset;
  float vel_1, vel_2, axes, vel_3, axis_tresh;
  bool button_check;

};


TeleopJoyMsg::TeleopJoyMsg(){

  //Default values for the parameters;
  vel_1 = 1.0;
  vel_2 = 1.0;
  vel_3 = 1.0;
  axis_tresh = 0.7;

  //Load of parameters
  nh.param("velocity_ab", vel_1, vel_1);
  nh.param("velocity_xy", vel_2, vel_2);
  nh.param("velocity_axis", vel_3, vel_3);
  nh.param("axis_treshold", axis_tresh, axis_tresh);

  // Publishing the message joy_controller::Joymsg in the topic
  //    named by "joy_cmd"
  cmd_pub = nh.advertise<joy_controller::Joymsg>("joy_cmd",10);

  // Subscribing at the topic joy receiving the message sensor_msgs::Joy
  //    This node calls TeleopJoyMsg::joyCallback everytime they receive
  //    a message from "joy"
  joy_sub = nh.subscribe<sensor_msgs::Joy>("joy",10,&TeleopJoyMsg::joyCallback,this);
}

void TeleopJoyMsg::joyCallback(const sensor_msgs::Joy::ConstPtr& joy)
{

  joy_controller::Joymsg joy_msg;

  axes = joy->axes[0];
  button_a = joy->buttons[0];
  button_b = joy->buttons[1];
  button_x = joy->buttons[2];
  button_y = joy->buttons[3];
  reset = joy->buttons[6];

  //Set of the treshold for manual command of the joystick

  if (axes > axis_tresh) {
    axes = 1.0;
  }
  else if (axes < -1*axis_tresh) {
    axes = -1.0;
  }
  else{
    axes = 0.0;
  }

  //Set functions for the buttons and axes.
  //  button_check exists to differe manual mode to automatic mode

  if (reset == 1){
    joy_msg.vel = 0;
    joy_msg.dir = 0;
    button_check = true;
    cmd_pub.publish(joy_msg);
  }
  else if (button_a == 1){
    joy_msg.vel = vel_1;
    joy_msg.dir = 1;
    cmd_pub.publish(joy_msg);
    button_check = true;
  }
  else if (button_b == 1){
    joy_msg.vel = vel_1;
    joy_msg.dir = -1;
    cmd_pub.publish(joy_msg);
    button_check = true;
  }
  else if (button_x == 1){
    joy_msg.vel = vel_2;
    joy_msg.dir = 1;
    cmd_pub.publish(joy_msg);
    button_check = true;
  }
  else if (button_y == 1){
    joy_msg.vel = vel_2;
    joy_msg.dir = -1;
    cmd_pub.publish(joy_msg);
    button_check = true;
  }
  else if (axes == 1.0 || axes == -1.0) {
    joy_msg.vel = vel_3;
    joy_msg.dir = int(axes);
    cmd_pub.publish(joy_msg);
    button_check = false;
  }
  else if (axes == 0.0 && button_check == false){
    joy_msg.vel = 0.0;
    cmd_pub.publish(joy_msg);
  }


}



int main(int argc, char** argv)
{

  ros::init(argc, argv, "teleop_joy_msg");

  TeleopJoyMsg teleop_joymsg;

  ros::spin();

}
