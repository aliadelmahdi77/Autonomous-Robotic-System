// #include "C:/dev/ros2_foxy/include/rclcpp/rclcpp.hpp"  // Use forward slashes
// #include "rclcpp/rclcpp.hpp"
#include <rclcpp/rclcpp.hpp>
 
#include <iostream>

int main(int argc, char **argv) {
    // Initialize ROS 2
    rclcpp::init(argc, argv);

    std::cout << "Hello, world! C++";

    // Shutdown ROS 2
    rclcpp::shutdown();
    return 0;
}