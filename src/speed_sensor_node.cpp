#include <vector>
#include <string>
#include <sstream>

#include "ros/ros.h"
#include "geometry_msgs/TwistStamped.h"
#include "serial.hpp"

ros::Publisher pub;
CustomSerial serial;

std::vector<std::string> split(std::string input, char delimiter)
{
  std::istringstream stream(input);
  std::string field;
  std::vector<std::string> result;
  while (std::getline(stream, field, delimiter))
  {
    result.push_back(field);
  }
  return result;
}

void sensor_update()
{
    // ----------------------------------------------
    // speed sensor data format
    // ----------------------------------------------
    // msg = "seq,pulse,ccw"
    // ----------------------------------------------
    // seq    uint8   0 ~ 255
    // pulse  uint8   0 ~ 255
    // ccw    bool    cw = 0, ccw = 1
    // ----------------------------------------------

    std::string data = serial.readMsg();
    if (data == "")
    {
        ROS_ERROR_STREAM("Failed to read sensor !");
        return;
    }

    ROS_INFO_STREAM();

    std::vector<std::string> vec = split(data, ',');
    int seq = std::stod(vec.at(0));
    int pluse = std::stod(vec.at(1));
    bool ccw = std::stod(vec.at(2));

    geometry_msgs::TwistStamped msg;
    msg.header.stamp = ros::Time::now();
    msg.header.frame_id = "base_link";
    msg.twist.linear.x = 0;

    pub.publish(msg);
}

void timer_callback(const ros::TimerEvent& e)
{
    sensor_update();
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "speed_sensor_driver");
    ros::NodeHandle nh;
    ros::NodeHandle pnh("~");

    std::string port;
    int freq, bandrate;

    pnh.param<int>("freq", freq, 50);
    pnh.param<std::string>("port", port, "/dev/ttyS0");
    pnh.param<int>("bandrate", bandrate, 9600);
    
    ROS_INFO_STREAM("freq: " << freq);
    ROS_INFO_STREAM("port: " << port);
    ROS_INFO_STREAM("bandrate: " << bandrate);

    if (freq < 0 || port == "" || bandrate < 0)
    {
        ROS_ERROR_STREAM("Invaild param !");
        return -1;
    }

    if (serial.openPort(port, bandrate) < 0)
    {
        ROS_ERROR_STREAM("Failed to connection !");
        return -1;
    }

    double rate = 1.0/freq;
    ros::Timer timer = nh.createTimer(ros::Duration(rate), timer_callback);
    pub = nh.advertise<geometry_msgs::TwistStamped>("/vehicle_twist", 1);

    ros::spin();

    return 0;
}
