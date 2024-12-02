#!/usr/bin/env python3
import rclpy as rc
from rclpy.node import Node  # Import the Node class

class LiDAR(Node):
    def __init__(self):
        super().__init__("LiDAR")
        self.counter1 =0
        self.get_logger().info("Hello ROS2")
        self.create_timer(0.5,self.timer_callback)

    def timer_callback(self):
        self.counter1 +=1
        self.get_logger().info("callback " + str(self.counter1))

def main(args=None):
    rc.init(args=args)

    #program starts

    node = LiDAR()
    rc.spin(node)

    # program ends

    rc.shutdown()

if __name__ == "__main__":
    main()
    

