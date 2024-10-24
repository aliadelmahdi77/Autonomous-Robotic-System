import sys
if sys.prefix == '/usr':
    sys.real_prefix = sys.prefix
    sys.prefix = sys.exec_prefix = '/home/aliadel/Documents/Autonomous-Robotic-System/install/py_pkg'
