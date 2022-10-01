# Speed Sensor ROS Driver

ROS driver for customized vehicle speed sensor.

Firmware -> [git]

## Build ( ROS Noetic )

```
cd ~/catkin_ws
source /opt/ros/noetic/setup.bash
catkin_make
```

## Launch

```
cd ~/catkin_ws
source devel/setup.bash
roslaunch speed_sensor_driver speed_sensor_driver.launch
```

## ROS Param

Default Settings

- freq : 50 (Hz)
- port : /dev/ttyS0
- bandrate : 9600 (bps)

---

2022.10 yudai.yamazaki
