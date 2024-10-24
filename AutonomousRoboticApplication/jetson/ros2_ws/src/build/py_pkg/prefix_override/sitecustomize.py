import sys
if sys.prefix == '/usr':
    sys.real_prefix = sys.prefix
    sys.prefix = sys.exec_prefix = '/home/aliadel/Documents/Autonomous-Robotic-System/AutonomousRoboticApplication/jetson/ros2_ws/src/install/py_pkg'
