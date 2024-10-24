#!/usr/bin/env python3
import rclpy as rc
from rclpy.node import Node  # Import the Node class
from example_interfaces.msg import String

class station(Node):
    def __init__(self):
        super().__init__("robotstation")
        self.counter1 =0
        self.publisher_ = self.create_publisher(String ,"robot_news",10)
        self.create_timer(0.5,self.publish_news)
        self.get_logger().info("The station has been started" )

    def publish_news(self):
        msg = String();
        msg.data = "Hello again"
        self.publisher_.publish(msg)
    

def main(args=None):
    rc.init(args=args)

    #program starts
    node = station()
    rc.spin(node)
    # program ends

    rc.shutdown()

if __name__ == "__main__":
    main()