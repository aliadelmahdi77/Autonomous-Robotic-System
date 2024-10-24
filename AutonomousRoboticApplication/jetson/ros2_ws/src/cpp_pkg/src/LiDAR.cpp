#include <rclcpp/rclcpp.hpp>
 
#include <iostream>
using namespace std; // Avoids needing std:: prefix

int main(int argc, char **argv) {
    // Initialize ROS 2
    rclcpp::init(argc, argv);

     // Create a ROS 2 node
    auto node = rclcpp::Node::make_shared("cpp_node");

    cout << "\nHello World\n\n";

    // Spin the node
    rclcpp::spin(node);

    // Shutdown ROS 2
    rclcpp::shutdown();
    return 0;
}



