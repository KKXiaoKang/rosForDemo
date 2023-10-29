import rclpy
from rclpy.node import Node

# 01 导入要发布的消息类型
from std_msgs.msg import String # pub 发布者
 
from std_msgs.msg import UInt32 # sub 订阅者

# 02 导入服务接口
"""
    (1)导入服务接口
        package.xml 下添加 <depend>village_interfaces</depend>的功能包依赖
        在py头文件添加 from village_interfaces.srv import BorrowMoney 导入接口
    (2)创建服务端回调函数
    (3)声明并创建服务端
    (4)编写回调函数逻辑处理请求
"""
# (1)
from village_interfaces.srv import BorrowMoney

class WriterNode(Node): # 作家节点继承于Node的节点的功能
    def __init__(self, name):
        # super()函数用于访问和调用一个对象上的父亲节点的函数
        super().__init__(name)
        # 打印函数
        self.get_logger().info(" 大家好！ 我是作家 %s 。" % name)

        # 通过父类的所继承的能力来创建好这个节点具有发布msg的功能
        # 02 声明并创建发布者
        # 第一个参数 话题的类型 
        # 第二个参数 话题的名字
        # 第三个参数 队列的大小
        # pub_novel 发布者变量名
        self.pub_novel = self.create_publisher(String, "my_first_PUB", 10)
        # self.pub_novel.publish() 在初始化的时候就可以选择发布消息
        
        # ROS当中的创建定时器的功能
        # 发布的次数
        self.count = 0
        self.timer_period= 5  # 定时器的定时周期为5
        self.timer = self.create_timer(self.timer_period, self.timer_callback)


        # 声明并创建订阅者
        # sub_money 订阅者变量名
        # 第一个参数 话题的类型 
        # 第二个参数 话题的名字
        # 第三个参数 当接收到订阅的消息后所做的处理
        # 第四个参数 队列的大小
        self.moneyCount = 80  # 当接收到订阅的消息后要存放在这里面的消息，这里比作小金库
        self.sub_money = self.create_subscription(UInt32, "my_first_money", self.recv_money_callback, 10)

        # 声明创建服务当作的服务端
        # (3)声明并创建服务端
        self.borrow_server = self.create_service(BorrowMoney, "borrow_money", self.borrow_money_callback)

        # 声明 1、声明参数
        self.declare_parameter("writer_timer_period", 5)

    # (2)创建服务端回调函数
    def borrow_money_callback(self,request,response):
        """
            (4)编写回调函数逻辑处理请求
            request 来自客户端的请求数据
            response 来自服务端的响应数据
        """
        self.get_logger().info("收到来自 : %s 的借钱请求， 账户目前有 : %d" % (request.name, self.moneyCount))

        # 借钱逻辑
        if request.money <= self.moneyCount * 0.1 :
            response.success = True
            response.money = request.money
            self.moneyCount = self.moneyCount - request.money
            self.get_logger().info("借钱成功，借出 %d ,目前还剩 %d " % (response.money, self.moneyCount))
        else:
            response.success = False
            response.money = 0
            self.get_logger().info("对不起，大兄弟，现在手头紧，不能借给你！")
        
        return response

        pass

    def timer_callback(self):
        # 仅仅用于 timer 定时器的回调函数
        # 每隔5s定时发布一个消息
        # 通过 ros2 interface show std_msgs/msg/String
        # 可以看到String里面有一个string data 我们需要对data进行赋值

        timer_period = self.get_parameter("writer_timer_period").get_parameter_value().integer_value
        self.timer.timer_period_ns = timer_period * (1000 * 1000 * 1000)

        msg = String() # 通过String这个类将msg实例化
        msg.data = "第 %d 次发布 第 %d 次消息" % (self.count, self.count)

        # 发布者发布消息(pub_novel本身不能用于函数进行调用，需要搭配.publish函数进行调用)
        self.pub_novel.publish(msg)

        # 获取log日志
        self.get_logger().info("发布了一个章节的小说，内容为 %s" % msg.data)

        # 每次发布完章节后自增1
        self.count +=1
        pass

    def recv_money_callback(self, money):
        # 订阅者订阅回调函数 当接收到信息后做相应处理
        # ros2 interface show std_msgs/msg/UInt32
        # uint32 data
        self.moneyCount += money.data
        self.get_logger().info('李四：我已经收到了%d的稿费' % self.moneyCount)

        # 接下来将使用命令行工具发布钱给李四
        ## ros2 topic pub /my_first_money std_msgs/msg/UInt32 "{data: 10}" 
        ## 上面是无限次循环给李四10块稿费
        ## ros2 topic pub /my_first_money std_msgs/msg/UInt32 "{data: 10}" -1 
        ## 上面是只发送一次
        pass
        

def main(args=None):
    """
    入口函数的位置
    ros2运行该节点的入口函数
    编写ROS2节点的一般步骤
    1. 导入库文件
    2. 初始化客户端库
    3. 新建节点对象
    4. spin循环节点
    5. 关闭客户端库
    """
    # rclpy.init(args=args) # 初始化rclpy
    # node = Node("li4")  # 新建一个节点
    # node.get_logger().info("大家好，我是作家li4.")
    # rclpy.spin(node) # 保持节点运行，检测是否收到退出指令（Ctrl+C）
    # rclpy.shutdown() # 关闭rclpy
    
    rclpy.init(args=args)  # 初始化rclpy    

    li4_node = WriterNode("li4") # 创建对象继承上面的节点

    rclpy.spin(li4_node) # 保持节点循环运行

    rclpy.shutdown()     # 关闭rclpy