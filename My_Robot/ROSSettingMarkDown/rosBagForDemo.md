# 时光记录仪 rosbag2

## 应用场景：激光雷达点云数据重放，用于二次构图
---

### ROS2中常用的一个CLI工具——rosbag2，这个工具用于记录话题的数据（就像小鱼录视频一样）。

---
/sexy_girl 为话题名字
```
ros2 bag record /sexy_girl # 录制话题
ros2 bag record topic-name1 topic-name2 # 记录多个话题的数据
ros2 bag record -a # 记录所有话题
ros2 bag record -o file-name topic-name # -o name 自定义输出文件的名字
ros2 bag info rosbag_xxx.db3 # 查看录制出话题的信息

ros2 bag play rosbag2_2023_09_21-23_11_18_0.db3 -r 10 # 10倍速播放话题
ros2 bag play rosbag2_2023_09_21-23_11_18_0.db3  # 默认1倍速播放话题
ros2 bag play rosbag2_2023_09_21-23_11_18_0.db3 -l # 循环播放话题 可以组合倍速使用
ros2 bag play rosbag2_2023_09_21-23_11_18_0.db3 --topics /my_first_PUB # 单独只播放一个话题的内容
```