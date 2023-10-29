# ROS2 节点管理之launch文件

## 1.1 需要启动的节点太多
## 1.2 节点之间有依赖关系管理

## ROS2编写launch的三种方法
* 1、python
* 2、xml
* 3、yaml

## 因为village_li 和 village_wang 的两个功能包的编译类型不同，所以编写launch的时候需要添加不同的指令进行launch管理

---
---
## Python功能包的launch添加 举例：village_li功能包 
### 1、在功能包下添加 launch文件夹 之后添加如下village.launch.py 的文件
```python
# 导入库
# 1.导入头文件
from launch import LaunchDescription
from launch_ros.actions import Node

# 2、定义
# 定义函数名称为：generate_launch_description
def generate_launch_description():
    
    # 3、创建节点描述
    # 创建Actions.Node对象li_node，标明李四所在位置
    li4_node = Node(
        package="village_li",
        executable="li4_node"
    )

    # 创建Actions.Node对象wang2_node,标明王二所在位置
    wang2_node = Node(
        package="village_wang",
        executable="wang2_node"
    )

    # 4、搭建描述launch
    # 创建LaunchDescription对象launch_description,用于描述launch文件
    launch_description = LaunchDescription([li4_node, wang2_node])

    # 返回让ROS2根据launch描述执行节点
    return launch_description
    pass
```
### 2、接下来修改setup.py 添加文件读取复制

```python
from setuptools import setup

# launch文件添加
from glob import glob
import os

package_name = 'village_li'

setup(
    name=package_name,
    version='0.0.0',
    packages=[package_name],
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
        (os.path.join('share', package_name, 'launch'),glob('launch/*.launch.py')) # 将launch文件下的所有launch复制到install/功能包/share下
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
            "li4_node=village_li.li4:main", # 重点新添加 搭配 source install/setup.bash 使用 这样子系统才能找到village_li这个包
            "li3_node=village_li.li3:main"
        ],
    },
)

```

---
---
## ament_cmake功能包的launch添加 举例：village_wang功能包

### 1、将上述python功能包下的 launch/village.laucnh.py 复制到 该c++节点下
### 2、在CMakeLists.txt下添加如下
```cmake
# 将launch文件添加到share下的功能包目录当中
install(DIRECTORY launch
  DESTINATION share/${PROJECT_NAME}
)
```

# ！特殊玩法：在launch当中添加参数的设置，前提是该节点已经成功设置好参数

```python
# 导入库
from launch import LaunchDescription
from launch_ros.actions import Node

# 定义函数名称为：generate_launch_description
def generate_launch_description():


    # 创建Actions.Node对象li_node，标明李四所在位置
    li4_node = Node(
        package="village_li",
        executable="li4_node",
        output='screen',  #四个可选项 
        parameters=[{'writer_timer_period': 1}]
        )
    # 创建Actions.Node对象wang2_node，标明王二所在位置
    wang2_node = Node(
        package="village_wang",
        executable="wang2_node",
        parameters=[{'novel_price': 2}]
        )

    # 创建另外一个命名空间下的，创建Actions.Node对象li_node，标明李四所在位置
    li4_node2 = Node(
        package="village_li",
        namespace="mirror_town",
        executable="li4_node",
        parameters=[{'writer_timer_period': 2}]
    )
    # 创建另外一个命名空间下的，Actions.Node对象wang2_node，标明王二所在位置
    wang2_node2 = Node(
        package="village_wang",
        namespace="mirror_town",
        executable="wang2_node",
        parameters=[{'novel_price': 1}]
    )

    # 创建LaunchDescription对象launch_description,用于描述launch文件
    launch_description = LaunchDescription([li4_node,wang2_node,wang2_node2,li4_node2])
    # 返回让ROS2根据launch描述执行节点
    return launch_description
```





