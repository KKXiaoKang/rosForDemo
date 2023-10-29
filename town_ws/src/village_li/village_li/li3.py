"""
    本代码旨在创建李三节点，用于借钱服务的客户端发出请求
"""
import rclpy
from rclpy.node import Node
from std_msgs.msg import String

# 1 导入服务接口
from village_interfaces.srv import BorrowMoney
"""
编写服务通信的客户端的一般步骤：

导入服务接口
创建请求结果接收回调函数
声明并创建客户端
编写结果接收逻辑
调用客户端发送请求

"""

class BaiPiaoNode(Node):
    """
        创建一个李三节点，并在初始化时输出一段话
    """
    def __init__(self, name):
        # 调用父类初始化函数
        super().__init__(name)

        # 打印相关信息
        self.get_logger().info("大家好，我是李三，李四的哥，买书的服务客户端创建！")

        # 要订阅的小说的内容，免费订阅
        self.sub_ = self.create_subscription(String,"my_first_PUB", self.recv_callback, 10) 

        # 3 声明并创建客户端
        self.borrow_client = self.create_client(BorrowMoney, "borrow_money")

    def recv_callback(self, novel):
        """
            订阅者接收数据后的回调函数
        """
        self.get_logger().info("李三:我已经收到了: %s" % novel.data)

    def borrow_moneyToEat(self, money=10):
        """
            调用成员函数，向服务端发送请求
        """
        self.get_logger().info("李三：开始借钱吃饭了，要借 %d 钱" % money)

        # 确认服务是否在线
        while not self.borrow_client.wait_for_service(1.0):
            # 如果服务在线 not True = False 跳出循环
            # 如果服务不在线 not False = True 则一直卡在循环
            # 参数1.0为每次等待1s看服务端有没有在线
            self.get_logger().warn("服务不在线，请你在等等。。。")

        # 构造请求内容
        #  
        request = BorrowMoney.Request() # BorrowMoney服务下有一个Request请求的初始化函数
        request.name = self.get_name() # 获取当前节点的名字
        request.money = money

        # 发送异步借钱请求
        # 发送请求后 add_done_callback用于接收response并做出响应处理
        self.borrow_client.call_async(request).add_done_callback(self.borrow_response_callback)

    # 2 创建请求结果接收回调函数
    def borrow_response_callback(self, response):
        """
            向服务端发出请求后, 服务端会返回response
            这个函数就是根据这个response返回的结果 来进行处理回调

            借钱结果回调
            4 编写结果接收逻辑
        """
        result = response.result() # 获取response里的数值
        if result.success:
            # 如果成功借到钱了
            self.get_logger().info(" 借到 %d 钱了,去吃麻辣烫了！" % result.money)
        else:
            # 如果没有借到钱
            self.get_logger().info(" 李三没有借到钱，借钱失败 。。。")
            pass





def main(args=None):
    """
        ros2运行该节点的入口函数,可配置函数名称
    """
    rclpy.init(args=args)
    node = BaiPiaoNode("li3") # 新建一个节点

    node.borrow_moneyToEat() # 调用借钱服务吃饭

    rclpy.spin(node) # 保持节点运行，检测是否收到退出命令（Ctrl + C）
    rclpy.shutdown() # rcl关闭


