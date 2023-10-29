# ROS2 实操项目讲解

## ROS 小车引脚
```
 +------+-----+----------+--------+---+   OPI5   +---+--------+----------+-----+------+
 | GPIO | wPi |   Name   |  Mode  | V | Physical | V |  Mode  | Name     | wPi | GPIO |
 +------+-----+----------+--------+---+----++----+---+--------+----------+-----+------+
 |      |     |     3.3V |        |   |  1 || 2  |   |        | 5V       |     |      |
 |   47 |   0 |    SDA.5 |     IN | 1 |  3 || 4  |   |        | 5V       |     |      |
 |   46 |   1 |    SCL.5 |     IN | 1 |  5 || 6  |   |        | GND      |     |      |
 |   54 |   2 |    PWM15 |     IN | 1 |  7 || 8  | 0 | IN     | RXD.0    | 3   | 131  |
 |      |     |      GND |        |   |  9 || 10 | 0 | IN     | TXD.0    | 4   | 132  |
 |  138 |   5 |  CAN1_RX |     IN | 0 | 11 || 12 | 1 | IN     | CAN2_TX  | 6   | 29   |
 |  139 |   7 |  CAN1_TX |     IN | 1 | 13 || 14 |   |        | GND      |     |      |
 |   28 |   8 |  CAN2_RX |     IN | 1 | 15 || 16 | 1 | IN     | SDA.1    | 9   | 59   |
 |      |     |     3.3V |        |   | 17 || 18 | 1 | IN     | SCL.1    | 10  | 58   |
 |   49 |  11 | SPI4_TXD |     IN | 1 | 19 || 20 |   |        | GND      |     |      |
 |   48 |  12 | SPI4_RXD |     IN | 1 | 21 || 22 | 1 | IN     | GPIO2_D4 | 13  | 92   |
 |   50 |  14 | SPI4_CLK |     IN | 1 | 23 || 24 | 1 | IN     | SPI4_CS1 | 15  | 52   |
 |      |     |      GND |        |   | 25 || 26 | 1 | IN     | PWM1     | 16  | 35   |
 +------+-----+----------+--------+---+----++----+---+--------+----------+-----+------+
 | GPIO | wPi |   Name   |  Mode  | V | Physical | V |  Mode  | Name     | wPi | GPIO |
 +------+-----+----------+--------+---+   OPI5   +---+--------+----------+-----+------+

7 8  一个轮子
11 12 一个轮子


```
## 一、自定义包创建
* 使用 ros2 pkg list 查看自己创建包是否存在
* 在town_ws文件夹下 使用 source install/setup.bash

* setup.py文件下修改自己的节点名称和指定main文件目录
```python
    setup(
    name=package_name,
    version='0.0.0',
    packages=[package_name],
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='orangepi',
    maintainer_email='orangepi@todo.todo',
    description='TODO: Package description',
    license='TODO: License declaration',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            "li5_node=village_li.li4:main" # 重点新添加 搭配 source install/setup.bash 使用 这样子系统才能找到village_li这个包
        ],
    },
)
```

* CMakeLists.txt 添加自己的节点文件
```cmake
#  ROS2 节点一定要添加的CMakeLists.txt的一些指令  #
# 添加要编译的cpp文件 未来可以拓展到include文件进行编译
add_executable(wang2_node src/wang2.cpp)

# 添加wang2_node的节点依赖于rclcpp
ament_target_dependencies(wang2_node rclcpp)

# 将编译好的文件放在大目录下的install下
install(TARGETS
  wang2_node
  DESTINATION lib/${PROJECT_NAME}
)
```
## 二、ros2通信机制
* Node李四 -> 发布 -> 《小说合集》 -> 订阅 -> Node王二

### （1）RQT工具之  rqt_graph
* 通过该命令 看到节点和节点的数据关系:
    1) 打开命令行
    2) 输入 rqt_graph
    3) 观察输出

### （2）ros2话题相关命令行界面 CLI 工具
* ros2 topic list
    1) 获取系统中当前活动的所有主题的列表
    2) 例子 /chatter

* ros2 topic list -t  
    1) 可以获取系统中当前活动的所有主题的列表 + 消息类型
    2) 例子 /chatter [std_msgs/msg/String]
    ```
    /chatter [std_msgs/msg/String]
    /parameter_events [rcl_interfaces/msg/ParameterEvent]
    /rosout [rcl_interfaces/msg/Log]
    ```

* ros2 topic echo /chatter
    1) 打印实时话题内容
    2) 终端一直输出话题的内容
    ```
    data: 'Hello World: 71'
    ---
    data: 'Hello World: 72'
    ---
    data: 'Hello World: 73'
    ---

    ```

* ros2 topic info /chatter
    1) 查看主题消息 包含发布者个数和订阅者个数 
    ```
    Type: std_msgs/msg/String
    Publisher count: 1
    Subscription count: 1
    ```

* ros2 interface show 
    1) 查看消息类型   
    ros2 interface show std_msgs/msg/String
    ```
    # This was originally provided as an example message.
    # It is deprecated as of Foxy
    # It is recommended to create your own semantically meaningful message.
    # However if you would like to continue using this please use the equivalent in example_msgs.

    string data
    ```

* ros2 topic pub arg 
    1) 手动发布命令  
    先关闭例程当中的发布者接下来输入   
    比如： ros2 topic pub /chatter std_msgs/msg/String 'data: "123"'
    ```
    publisher: beginning loop
    publishing #1: std_msgs.msg.String(data='123')

    publishing #2: std_msgs.msg.String(data='123')

    publishing #3: std_msgs.msg.String(data='123')

    publishing #4: std_msgs.msg.String(data='123')

    publishing #5: std_msgs.msg.String(data='123')
    ```

## 编译包选项
```
编译一个单独的包 
colcon build --packages-select <name-of-pkg>

但这个指令并不会编译该包的依赖，往往会报错。可以用下面这条指令进行包和其依赖编译
colcon build --packages-up-to <name-of-pkg>
```

## 三、话题的发布（Publisher）与订阅（subscriber）实现
`
### 1、Python
#### （1） Python话题发布者（Publisher）编写一个话题发布者的流程如下：
* 01 导入消息类型
* 02 声明并创建发布者
* 03 编写发布逻辑发布数据

``` 
重要小知识,允许通过更改src下的部分文件来改变install
colcon build --symlink-install
```
#### （2） Python话题订阅者（subscriber）编写一个话题订阅者的流程如下：
* 01 导入订阅的话题接口类型
* 02 创建订阅回调函数
* 03 声明并创建订阅者
* 04 编写订阅回调处理逻辑

### 2、C++
#### （1）C++ 话题发布者（Publisher）编写一个话题发布者的流程如下：
* 01 导入消息类型
* 02 声明并创建发布者
* 03 编写发布逻辑发布数据

#### （2） C++ 话题订阅者（subscriber）编写一个话题订阅者的流程如下：
* 01 导入订阅的话题接口类型
* 02 创建订阅回调函数
* 03 声明并创建订阅者
* 04 编写订阅回调处理逻辑

## 四、ROS2接口介绍（更好的编写机器人功能协调）
1、查看ROS2中的默认接口
```
ros2 interface package sensor_msgs
```
通过该命令可以查看某一个接口包下所有的接口（举例演示查看传感器类的消息包）

```
打开终端输入：ros2 interface package sensor_msgs
sensor_msgs/msg/JointState  #机器人关节数据
sensor_msgs/msg/Temperature #温度数据
sensor_msgs/msg/JoyFeedbackArray 
sensor_msgs/msg/Joy
sensor_msgs/msg/PointCloud2 #点云
sensor_msgs/msg/MultiEchoLaserScan 
sensor_msgs/msg/NavSatStatus 
sensor_msgs/msg/CameraInfo #相机信息
sensor_msgs/msg/Illuminance 
sensor_msgs/msg/MagneticField
sensor_msgs/srv/SetCameraInfo
sensor_msgs/msg/LaserEcho 
sensor_msgs/msg/RegionOfInterest
sensor_msgs/msg/PointCloud #点云
sensor_msgs/msg/Range #范围
sensor_msgs/msg/RelativeHumidity
sensor_msgs/msg/FluidPressure
sensor_msgs/msg/BatteryState
sensor_msgs/msg/Imu #加速度传感器
sensor_msgs/msg/Image #图像
sensor_msgs/msg/PointField
sensor_msgs/msg/JoyFeedback
sensor_msgs/msg/LaserScan #雷达数据
sensor_msgs/msg/MultiDOFJointState #多自由度关节数据
sensor_msgs/msg/TimeReference 
sensor_msgs/msg/CompressedImage #压缩图像
sensor_msgs/msg/NavSatFix 
sensor_msgs/msg/ChannelFloat32


最新版本显示如下：
sensor_msgs/msg/JointState
sensor_msgs/msg/JoyFeedback
sensor_msgs/msg/FluidPressure
sensor_msgs/msg/CameraInfo
sensor_msgs/msg/TimeReference
sensor_msgs/msg/Range
sensor_msgs/msg/ChannelFloat32
sensor_msgs/msg/MultiEchoLaserScan
sensor_msgs/srv/SetCameraInfo
sensor_msgs/msg/Temperature
sensor_msgs/msg/JoyFeedbackArray
sensor_msgs/msg/PointCloud2
sensor_msgs/msg/CompressedImage
sensor_msgs/msg/PointCloud
sensor_msgs/msg/Image
sensor_msgs/msg/Joy
sensor_msgs/msg/RegionOfInterest
sensor_msgs/msg/RelativeHumidity
sensor_msgs/msg/MagneticField
sensor_msgs/msg/NavSatStatus
sensor_msgs/msg/LaserEcho
sensor_msgs/msg/Illuminance
sensor_msgs/msg/NavSatFix
sensor_msgs/msg/LaserScan
sensor_msgs/msg/Imu
sensor_msgs/msg/BatteryState
sensor_msgs/msg/MultiDOFJointState
sensor_msgs/msg/PointField
```

## 五、除了官方给的std_msgs 和 sensor_msgs 接口外，还可以自定义接口
### 除了参数之外，话题、服务和动作(Action)都支持自定义接口，每一种通信方式所适用的场景各不相同，所定义的接口也被分为话题接口、服务接口、动作接口三种。

这三种接口定义起来有什么不一样的地方呢？

* 话题接口格式：xxx.msg
```
int64 num
```

* 服务接口格式：xxx.srv
```
int64 a
int64 b
---
int64 sum
```


* 动作接口格式：xxx.action
```
int32 order
---
int32[] sequence
---
int32[] partial_sequence
```

## 六、自定义组件服务消息
* 具体详细可查看village_interfaces功能包下的README.md文件