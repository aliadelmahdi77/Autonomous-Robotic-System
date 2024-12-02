import sys
if sys.prefix == 'c:\\python38':
    sys.real_prefix = sys.prefix
    sys.prefix = sys.exec_prefix = 'D:\\Shared Folders\\Uni\\courses\\Arm stm\\Graduation Project\\Autonomous Robotic System\\AutonomousRoboticApplication\\raspberry_pi\\src\\ros2_ws\\install\\py_pkg'
