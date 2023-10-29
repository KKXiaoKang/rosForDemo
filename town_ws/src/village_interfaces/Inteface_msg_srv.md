##  自定义消息服务接口
* （1）创建msg文件夹 同时编写 Novel.msg
```msg
# 原始数据类型
# bool
# byte
# char
# float32,float64
# int8,uint8
# int16,uint16
# int32,uint32
# int64,uint64
# string

# 调用原始数据类型
# 或者std_msgs/msg/string
string content

# 调用已有的数据类型
sensor_msgs/Image image
```
* （2）在CMakeLists.txt添加如下
```CMake
# 添加对sensor_msgs的
find_package(sensor_msgs REQUIRED)
find_package(rosidl_default_generators REQUIRED)

# 添加消息文件和依赖
rosidl_generate_interfaces(${PROJECT_NAME}
  "msg/Novel.msg"
   DEPENDENCIES sensor_msgs
 )
```

* （3）在package.xml文件添加如下依赖
```xml
<!--> 添加如下依赖 <!-->
  <depend>sensor_msgs</depend>
  <build_depend>rosidl_default_generators</build_depend>
  <exec_depend>rosidl_default_runtime</exec_depend>
  <member_of_group>rosidl_interface_packages</member_of_group>
```

## 验证自己写的自定义接口是否正确

```
source install/setup.bash
ros2 interface package village_interfaces # 查看包下所有接口
ros2 interface show village_interfaces/msg/Novel # 查看内容
ros2 interface proto village_interfaces/msg/Novel # 显示属性
```
