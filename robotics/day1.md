ros2 run tutorial_1 sender


ros2 topic list
/scan

ros2 topic type /cmd_vel
geometryh

ros2 interface show geometry_mesgs/msg/Twist
// import twist and vector space

// see scan 
ros2 topic type /scan

ros2 interface show geometry_mesgs/msg/Twist

float32 ranges (default 0-359)
// get distance in front of you: range[0]
// rangeMax: max distance lidar can see 

// from geom
