import rclpy
from rclpy.node import Node

class LocalizationNode(Node):
    
    def __init__(self):
        super().__init__('localization_node')
        self.get_logger().info('localization node 已经开启！')

def main(args=None):
    rclpy.init(args=args) # 初始化rclpy
    
    node = LocalizationNode() # 创建定位节点

    rclpy.spin(node)  # 保持节点循环运行

    node.destroy_node() # 关闭节点

    rclpy.shutdown()  # 关闭rclpy

if __name__ == '__main__':
    main()