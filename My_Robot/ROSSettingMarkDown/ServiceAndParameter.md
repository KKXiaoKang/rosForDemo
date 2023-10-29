# 个人机器人控制器架构
```
# 创建工作空间同时进入要创建包的位置
cd code/
mkdir -p My_Robot/src
cd My_Robot/src

```

* 最初文件里面只会有My_Robot文件夹和src文件夹

```
接下来执行

ros2 pkg create chassis_control --build-type ament_cmake --dependencies rclcpp

创建自己第一个底盘控制包
就会在src下生成功能包
```
* 创建python功能包
```
ros2 pkg create village_li --build-type ament_python --dependencies rclpy
```
* 回到code/My_Robot 文件夹下
```
输入命令

colcon build

即使chassis_control包里面没有写文件，也会进行编译
```

编译完成后
My_Robot文件夹下将会多出来build install log 三个文件夹和 src存放功能包的同级目录




-------------------------
-------------------------
-------------------------

# 小车引脚图详解
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
```

 # ！（重点必看） 开始ROS架构前 ———————— ROS下常见的节点 之间 信息传递方法
 ##
 * 话题-topics
 * 服务-services
 * 动作-Action
 * 参数-parameter
 ## （1）  话题（topic） 话题涉及到发布者和订阅者 (话题是没有返回的，用于单向或大量的数据传递)
 * 比如事例里面讲到的李四写小说 小说作为topic被发布者李四发布出去，由订阅者张三负责接收
 * 发布的消息类型可以是std_msgs下的通用消息类型和ROS下的机器人常见消息类型（已定义好）
 * 发布的消息类型也可以是自定义village_interfaces下的自定义msg消息类型（自己进行消息组合）
 ## （2）  服务 services 涉及到客户端和服务端 之间的交互 （服务是双向的，客户端发送请求，服务端响应请求）
 * 比如等下要讲到的借钱事宜（通过定义一个服务来相互进行交互）
 * (1) 李三借钱 （ 创造一个借钱服务接口 ） 
 * (2) 王二与二手书 （ 创造一个买书服务接口 ）

服务流程如下
```flow
    -------------  服务端  <----------
    |                                |
    |                                |
发送响应-借钱结果               发送请求-欠条
    |                                |
    |                                |
    ---------->    客户端  ------------
```

* 服务注意事项
  * (1) 同一个服务（名称相同）有且只能有一个节点来提供
  * (2) 同一个服务可以被多个客户端调用

* 使用服务时的一些可用命令便于方便查看调试
  * ros2 service list  # 列出当前所有服务的列表
  * ros2 service type /add_two_inis  #列出该服务的接口类型
  * ros2 interface show  xxxx # 使用该命令查找上面接口类型的具体数据定义是如何的
  * ros2 service find example_interfaces/srv/AddTwoInts # 查找使用该接口类型的数据节点的服务是哪个

-----------

  ### 自定义服务接口格式：xxx.srv
  ```
  int64 a
  int64 b
  ---
  int64 num
  ```
  上方的是客户端发送请求的数据结构定义
  下方的是服务端响应结果的数据结构定义

  编写自定义服务接口如下
  * (1) 新建srv文件夹，并在文件夹下新建xxx.srv
  * (2) 在xxx.srv下编写服务接口内容并保存
  * (3) 在CmakeLists.txt添加依赖和srv文件目录
  * (4) 在package.xml中添加xxx.srv所需的依赖
  * (5) 编译功能包即可生成python与C++头文件
-----------
-----------
-----------
-----------
---
---
## ！开始编写编写Python服务！
### 1、服务 服务器 的创建 以li4_node节点为例子 按照下面步骤
* (1)导入服务接口
    * package.xml 下添加 <depend>village_interfaces</depend>的功能包依赖
    * 在py头文件添加 from village_interfaces.srv import BorrowMoney 导入接口
* (2)创建服务端回调函数
* (3)声明并创建服务端
* (4)编写回调函数逻辑处理请求

### 2、然后输入 colcon build --packages-select village_li 编译功能包
### 3、再启动节点 ros2 run village_li li4_node 
### 4、再输入下面命令call一下服务 
* ros2 service call /borrow_money  village_interfaces/srv/BorrowMoney "{name: 'fish', money: 5}"
* 命令行输出
```
waiting for service to become available...
requester: making request: village_interfaces.srv.BorrowMoney_Request(name='fish', money=5)

response:
village_interfaces.srv.BorrowMoney_Response(success=True, money=5)
```
---
---
### 2、服务 客户端的创建 以li4_node节点为例子 按照下面步骤
### 编写服务通信的客户端的一般步骤：

- 1 导入服务接口
- 2 创建请求结果接收回调函数
- 3 声明并创建客户端
- 4 编写结果接收逻辑
- 5 调用客户端发送请求

---
---
---
---
---
---
---

## ！开始编写编写C++服务 ！
- 以wang2_node节点作为例子
### 编写ROS2服务通信服务端步骤
### 1、导入服务接口
### 2、创建服务端回调函数
### 3、声明并创建服务端
### 4、编写回调函数逻辑处理请求

---
---
### 编写ROS2服务通信客户端步骤
- 以zhang3_node节点作为例子
### 1、导入服务接口
### 2、创建请求结果接收回调函数
### 3、声明并创建客户端
### 4、编写结果接收逻辑
### 5、调用客户端发送请求
 

 ## （3）  参数parameter 参数是节点的一个配置值，你可以任务参数是一个节点的设置
* bool 和bool[]，布尔类型用来表示开关，比如我们可以控制雷达控制节点，开始扫描和停止扫描。
* int64 和int64[]，整形表示一个数字，含义可以自己来定义，这里我们可以用来表示李四节点写小说的周期值
* float64 和float64[]，浮点型，可以表示小数类型的参数值
* string 和string[]，字符串，可以用来表示雷达控制节点中真实雷达的ip地址
* byte[]，字节数组，这个可以用来表示图片，点云数据等信息

 ### ROS2的参数是由键值组成的
 * 名字：李四写小说周期, 值：5s
 * 名字：显示器亮度， 值：60%

### 常见参数的命令行
 ```
 ros2 param list                             # 查看目前节点的所有参数
 ros2 param describe /turtlesim background_b # 查看某节点下的一个参数的所有描述
 ros2 param get /turtlesim background_b      # 获取某节点下的一个参数的当前值
 
 ros2 param set /turtlesim background_g 156  # 设置某节点的一个参数的值
                                             # 调用该命令时只是临时修改

 ros2@ubuntu: ros2 param dump /turtlesim     # 保存某节点的参数值（拍照参数截屏）
 Saving to: ./turtlesim.yaml 

 使用 cat ./turtlesim.yaml 的命令查看参数

 重新启动ROS节点还是会变成默认值，但此时我们有了yaml文件，可以快速读取参数
 使用
 ros2 param load /turtlesim ./turtlesim.yaml
 命令快速加载存在yaml里的参数   

 当然以上还是会慢一步，先开始默认节点，在使用ros param load的命令加载参数
 有没有什么方法可以一开节点就自动加载列表呢，有，很简单
 ros2 run turtlesim turtlesim_node --ros-args --params-file ./turtlesim.yaml
 使用该命令在开启节点的时候就把参数yaml加载进去      
 ```

```python
ros2 topic hz /my_first_PUB # 查看该话题的发布速度

li4.py文件当中使用
# 声明 1、声明参数
self.declare_parameter("writer_timer_period", 5)

# 使用获取 2、时间周期中获取发布小说速度的参数
timer_period = self.get_parameter("writer_timer_period").get_parameter_value().integer_value
self.timer.timer_period_ns = timer_period * (1000 * 1000 * 1000)
```

```c++
// wang2.cpp 文件使用
// 书本的单价 参数类型
unsigned int novel_price = 1; // 目前书本的单价为1 

// 声明参数
this->declare_parameter<std::int64_t>("novel_price", novel_price);

// 获取书本最新的单价
this->get_parameter("novel_price", novel_price);
```

 ## （4）  Action 动作 

流程是张三将钱通过服务给王二，然后王二凑够对应章节数量的小说返回给张三，这个过程看似没有问题，假设你是张三，你就会发现下面这些问题：

* 你把100块钱给了王二，你并不知道王二有没有收到自己的钱（不能确认服务端接收并处理目标）
* 假设王二收到了，但库存没有100章的小说，王二开始攒小说，此时你也无法得知王二攒小说的进度（没有反馈）
* 假设王二攒小说攒一半，你不想要了，也没办法通知王二退款

如果这些问题体现在机器人上，可能是这样子的。我们通过服务服务发送一个目标点给机器人，让机器人移动到该点：
* 你不知道机器人有没有处理移动到目标点的请求（不能确认服务端接收并处理目标）
* 假设机器人收到了请求，你不知道机器人此时的位置和距离目标点的距离（没有反馈）
* 假设机器人移动一半，你想让机器人停下来，也没有办法通知机器人

上面的场景在机器人控制当中经常出现，比如控制导航程序，控制机械臂运动，控制小乌龟旋转等，很显然单个话题和服务不能满足我们的使用，因此ROS2针对控制这一场景，基于原有的话题和服务，设计了动作（Action）这一通信方式来解决这一问题。

---
---
### 参数是由服务构建出来了，而Action是由话题和服务共同构建出来的（一个Action = 三个服务+两个话题） 

### 三个服务分别是：
* 1.目标传递服务 
* 2.结果传递服务 
* 3.取消执行服务 

### 两个话题：
- 1.反馈话题（服务发布，客户端订阅） 
- 2.状态话题（服务端发布，客户端订阅）

```
ros2 action list # 查看当前获取系统中的action列表
ros2 action list -t # 查看所有action列表 同时查看类型
ros2 interface show xxx # 查看该类型的动作下的自定义服务接口是什么数据类型
ros2 action info xxx # 通过action的名字来查看这个action的客户端和服务端的数量以及名字
ros2 action send_goal /turtle/rotate_absolute turtlesim/action/RotateAbsolute "{theta: 0}" # 发送action请求到服务端，这里演示的是发送小乌龟转动的绝对角度给服务端

ros2 action send_goal /turtle/rotate_absolute turtlesim/action/RotateAbsolute "{theta: 0}" --feedback # 通过使用feedback将每一个时刻内小乌龟的弧度进行命令行打印
```