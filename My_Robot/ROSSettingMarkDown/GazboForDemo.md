# Gazebo VS Rviz2
## Gazebo 可视化工具

## Gazebo 集成ROS2

## Gazebo与 ros版本的集成是通过一组叫做gazebo_ros_pkgs 的包晚餐的

```
Gazebo -> [API] -> gazebo_ros-pkgs -> [ROS2通信机制] -> ROS2
```

```
sudo apt install gazebo11 # 安装gazebo
sudo apt install ros-foxy-gazebo-* # 安装gazebo的包
gazebo /opt/ros/foxy/share/gazebo_plugins/worlds/gazebo_ros_diff_drive_demo.world # 一键运行两轮差速demo
```

# 控制两轮差速小车
```
ros2 topic list -t # 查看打开小车后的话题和话题类型
其中聚焦在 /demo/cmd_demo这个话题当作 通过这个话题可以轻松控制小车

ros2 topic pub /demo/cmd_demo geometry_msgs/msg/Twist "{linear:{x: 0.5,y: 0,z: 0},angular: {x: 0, y: 0,z: 0}}"
# 输入上述命令即可控制小车以0.5m/s的速度往前行驶

ros2 topic pub /demo/cmd_demo geometry_msgs/msg/Twist "{linear:{x: 0,y: 0,z: 0},angular: {x: 0, y: 0,z: 0}}"
# 输入上述命令即可让小车 0m/s停下来
```