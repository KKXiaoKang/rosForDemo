/**
 *  编写ROS2节点的一般步骤
    1. 导入库文件
    2. 初始化客户端库
    3. 新建节点对象
    4. spin循环节点
    5. 关闭客户端库
*/

#include "rclcpp/rclcpp.hpp"
#include <iostream>

using namespace std;

class SingleDogNode: public rclcpp::Node
{
private:
    /* data */
public:
    SingleDogNode(std::string name):Node(name)
    {
        // 打印
        RCLCPP_INFO(this->get_logger(), "大家好 . 我是读者 %s.", name.c_str());
    }

};


int main(int argc, char ** argv) // argc 参数的数量 argv 参数的数组
{
    rclcpp::init(argc, argv); // 初始化rclcpp
    /* 产生一个 wang2的 节点 使用智能指针*/
    auto node =  std::make_shared<SingleDogNode>("wang2");
    rclcpp::spin(node); // 循环node节点
    rclcpp::shutdown(); // 关闭rclcpp库


    return 0;
}