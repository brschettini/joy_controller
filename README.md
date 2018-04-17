# Publishing a custom ROS message using a joystick

This program is used to send a custom message using a joystick. For instance, this program only works for a XBox 360 controller. If you want to use another controller, please visit [this page](http://wiki.ros.org/joystick_remapper).

The launch file [joy_cont.launch](https://github.com/brschettini/joy_controller/blob/master/launch/joy_cont.launch) starts three ROS nodes, as you can see typing `rqt_graph` in your command line.

![joy_controller_nodes](https://user-images.githubusercontent.com/33843749/38881899-49bf58c4-423f-11e8-8dca-56ef0f4ae797.png)

Note that the float64 node sends a `std_msg::Float64` message to the topic `pan_controller/command`. This node has been made to control a [Dynamixel Driver](http://wiki.ros.org/dynamixel_controllers) in Wheel mode just for learning purpose.

## Getting Started

Before using this package, please visit the [Joystick Configuring Tutorial](http://wiki.ros.org/joy/Tutorials/ConfiguringALinuxJoystick) so the joy node can be started without issues.

After, clone this repository:

```git clone https://github.com/brschettini/joy_controller```

Source the setup.bash:

```source your/catkin/workspace/devel/setup.bash```

And finally start the launch:

```roslaunch joy_controller joy_cont.launch```


# Authors

* **Bruno Schettini** - *Initial Work* - [brschettini](https://github.com/brschettini)
