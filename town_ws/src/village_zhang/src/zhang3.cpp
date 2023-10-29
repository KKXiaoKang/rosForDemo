#include "rclcpp/rclcpp.hpp"

// ### 1、导入服务接口
#include "village_interfaces/srv/sell_novel.hpp"

/**
 * 
 * 
### 1、导入服务接口
### 2、创建请求结果接收回调函数
### 3、声明并创建客户端
### 4、编写结果接收逻辑
### 5、调用客户端发送请求
*/

// 提前声明的占位符，留着创建客户端的时候用
using std::placeholders::_1;

/*
    创建一个类节点，名字叫做PoorManNode,继承自Node.
*/
class PoorManNode : public rclcpp::Node
{

public:
    /* 构造函数 */
    PoorManNode(std::string name) : Node(name)
    {
        // 打印一句自我介绍
        RCLCPP_INFO(this->get_logger(), "大家好，我是得了穷病的张三.");

        // 创建客户端
        // ### 3、声明并创建客户端
        novel_client = this->create_client<village_interfaces::srv::SellNovel>("sell_novel");
    }

    /* ### 5、调用客户端发送请求 */
    void buy_novels()
    {
        RCLCPP_INFO(this->get_logger(), "我是张三，准备去买小说了");
        // 1、等待服务端上线
        while (!novel_client->wait_for_service(std::chrono::seconds(1))) // 每隔1s检查服务端是否上线 not False = True
        {
            /* 打印 */
            RCLCPP_WARN(this->get_logger(), "等待服务端上线。。。。。");
        }
        
        // 2、构造请求数据
        auto request = std::make_shared<village_interfaces::srv::SellNovel_Request>(); // 赋值智能指针 同时将SellNovel自定义服务接口的数据类型告诉它
        request->money = 5;

        // 3、发送异步请求
        novel_client->async_send_request(request, std::bind(&PoorManNode::novels_callback, this, _1));
    }
private:

    // 创建服务的客户端
    rclcpp::Client<village_interfaces::srv::SellNovel>::SharedPtr novel_client;

    // 注意参数与服务端有所不同
    // 编写接收小说结果的回调函数
    // ### 2、创建请求结果接收回调函数

    void novels_callback(rclcpp::Client<village_interfaces::srv::SellNovel>::SharedFuture response)
    {
        // ### 4、编写结果接收逻辑
        auto result = response.get(); // 自动获取结果并且转换类型

        // 打印
        RCLCPP_INFO(this->get_logger(), "收到了  %d  章节的小说， 现在开始按章节读",result->novels.size());

        // 通过遍历方法
        for(std::string novel:result->novels)
        {
            // 通过novel临时string变量把每一个章节的小说打印出来 并且c_str c语言转字符
            RCLCPP_INFO(this->get_logger(), "%s", novel.c_str());
        }

        // 结束
        RCLCPP_INFO(this->get_logger(), "小说读取完毕，十分不错，后面可以放进我的书库里！");
    }
};

/*主函数*/
int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    /*产生一个Zhang3的节点*/
    auto node = std::make_shared<PoorManNode>("zhang3");

    // 调用服务端发送服务请求
    node->buy_novels();

    /* 运行节点，并检测rclcpp状态*/
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}