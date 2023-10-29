/**
 *  编写ROS2节点的一般步骤
    1. 导入库文件
    2. 初始化客户端库
    3. 新建节点对象
    4. spin循环节点
    5. 关闭客户端库
*/

/**
 * 编写ROS2服务 服务端的一般步骤
    1、导入服务接口
    2、创建服务端回调函数
    3、声明并创建服务端
    4、编写回调函数逻辑处理请求
*/
#define MULTI_THREAD_MODE

#include "rclcpp/rclcpp.hpp"
#include <iostream>
// 以下为C++创建订阅者
// 1.导入要订阅的消息类型 std_msgs/mssg/String
#include "std_msgs/msg/string.hpp"

// 1.导入要发布的消息类型
#include "std_msgs/msg/u_int32.hpp"

// (1) 导入服务接口
#include "village_interfaces/srv/sell_novel.hpp"
#include <queue>  // 创建队列来接收小说

using namespace std;

using std::placeholders::_1; //占位符号 1 1个参数占用1个位置
using std::placeholders::_2; //占位符号 2 2个参数占用2个位置

class SingleDogNode: public rclcpp::Node
{
private:
    /* data */

    // 3 声明订阅者
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr sub_novel;

    // 3 声明话题发布者
    rclcpp::Publisher<std_msgs::msg::UInt32>::SharedPtr pub_money; 

    // (2)解决书库进队和卖书出队的死锁问题
    // 声明一个创建回调组
    rclcpp::CallbackGroup::SharedPtr sell_novels_callback_group;

    // （2）服务接收文字队列
    // 书库
    std::queue<std::string> novels_queue;

    // 书本的单价 参数类型
    unsigned int novel_price = 1; // 目前书本的单价为1

    // （3） 声明服务端
    rclcpp::Service<village_interfaces::srv::SellNovel>::SharedPtr sell_server;

    // 2 创建回调函数
    void novel_callback(const std_msgs::msg::String::SharedPtr novels)
    {
        // 4 当收到发过来的文稿的时候就发布稿费给
        // 编写发布逻辑发布数据
        std_msgs::msg::UInt32 money;
        money.data = 10;
        // 发布钱
        pub_money->publish(money);

        // （2）收到书之后把书放进书库里
        novels_queue.push(novels->data);

        // 4 编写回调逻辑
        RCLCPP_INFO(this->get_logger(), "我已经阅读 %s.", novels->data.c_str());
    }

    // (2) 创建服务端回调函数
    void sell_novel_callback(const village_interfaces::srv::SellNovel::Request::SharedPtr request,
                             const village_interfaces::srv::SellNovel::Response::SharedPtr response)
    {
        // 判断当前的书章节数量够不够，不够就要攒书，再返回
        // 等待novels_queue 书库里的书的数量达到我们要卖出去的
        // 等待会让当前的线程堵塞
        RCLCPP_INFO(this->get_logger(), "收到一个买书的请求， 一共给了 %d 元 ", request->money);

        // 获取书本最新的单价
        this->get_parameter("novel_price", novel_price);

        // 计算应该返回给客户端的小说数量
        unsigned int novelNum = (int)request->money / (1.0);

        // 通过数量进行判断
        if (novelNum > novels_queue.size())
        {
            // 等待 凑齐书
            RCLCPP_INFO(this->get_logger(), "书不够， 书库有 %d 要卖出 %d", novels_queue.size(), novelNum);

            // 每1s执行一次的循环体
            rclcpp::Rate rate(1);

            // 等待书本凑齐
            while(novels_queue.size() < novelNum)
            {
                RCLCPP_INFO(this->get_logger(), "等待中 ，目前还差 %d 的书", novelNum - novels_queue.size());

                rate.sleep();
            }
        }

        RCLCPP_INFO(this->get_logger(), "当前书库里的书有 %d, 大于要卖出去的书的数量 %d", novels_queue.size(), novelNum);

        // 开始卖书
        for(int i =0; i < (int)novelNum; i++)
        {
            // 先把该节点novels_queue的书库的第一头部书放到 回应的书本小说数组末尾
            response->novels.push_back(novels_queue.front());
            // 接下来书库调用pop出队列操作
            novels_queue.pop();
        }
    }   

public:
    SingleDogNode(std::string name):Node(name)
    {
        // 打印
        RCLCPP_INFO(this->get_logger(), "大家好 . 我是读者 %s.", name.c_str());
        // 3.创建订阅者
        // 正常来说我们的回调函数都是成员函数，在创建实例化对象的时候若想同时调用成员函数，需要使用c11新特性 bind
        // bind函数中
        // 第一个参数为 你所需要调用的类的成员函数
        // 第二个参数为 哪个对象需要调用 如果用this就代表本对象
        // 第三个参数为 占位符
        // 因为只有一个参数所以使用 _1
        sub_novel = this->create_subscription<std_msgs::msg::String>("my_first_PUB", 10, std::bind(&SingleDogNode::novel_callback, this, _1));

        // 3.创建话题发布者
        pub_money = this->create_publisher<std_msgs::msg::UInt32>("my_first_money", 10);


        // (3)实例化自定义回调函数组
        sell_novels_callback_group = this->create_callback_group(rclcpp::CallbackGroupType::MutuallyExclusive);
        // (3)实例化服务端
        // bind 将成员函数转换为回调函数
        // 因为有两个参数所以使用 _1 和 _2
        sell_server = this->create_service<village_interfaces::srv::SellNovel>("sell_novel", std::bind(&SingleDogNode::sell_novel_callback, this, _1, _2),
                                                                                rmw_qos_profile_default,
                                                                                sell_novels_callback_group);

        // 声明参数
        this->declare_parameter<std::int64_t>("novel_price", novel_price);
    }

};


int main(int argc, char ** argv) // argc 参数的数量 argv 参数的数组
{
    // ------ 多线程模式 ------ //
    #ifdef MULTI_THREAD_MODE
    rclcpp::init(argc, argv); // 初始化rclcpp
    /* 产生一个 wang2的 节点 使用智能指针*/
    auto node =  std::make_shared<SingleDogNode>("wang2");

    // 声明执行器
    // 多线程执行
    rclcpp::executors::MultiThreadedExecutor executor;
    executor.add_node(node);
    executor.spin();

    // rclcpp::spin(node); // 循环node节点
    rclcpp::shutdown(); // 关闭rclcpp库


    return 0;

    #endif
    // ------ 多线程模式 ------ //

    // ------ 单线程模式 ------ //
    #ifndef MULTI_THREAD_MODE
    rclcpp::init(argc, argv); // 初始化rclcpp
    /* 产生一个 wang2的 节点 使用智能指针*/
    auto node =  std::make_shared<SingleDogNode>("wang2");

    // // 声明执行器
    // // 多线程执行
    // rclcpp::executors::MultiThreadedExecutor executor;
    // executor.add_node(node);
    // executor.spin();

    rclcpp::spin(node); // 循环node节点
    rclcpp::shutdown(); // 关闭rclcpp库


    return 0;

    #endif
    // ------ 单线程模式 ------ //
}