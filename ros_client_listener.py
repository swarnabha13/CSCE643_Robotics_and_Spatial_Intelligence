#!/usr/bin/env python3
import socket
import select
import rospy
from std_msgs.msg import String
from geometry_msgs.msg import Twist

def talker(data):
    rospy.init_node('talker_relay', anonymous = True)
    velocity_publisher = rospy.Publisher('/turtle1/cmd_vel', Twist, queue_size=10)
    vel_msg = Twist()
    vel_msg.linear.x = 0
    vel_msg.linear.y = 0
    vel_msg.linear.z = 0
    vel_msg.angular.x = 0
    vel_msg.angular.y = 0
    vel_msg.angular.z = 0

    #rate = rospy.Rate(10)
    #while not rospy.is_shutdown():
    if(data == 'w'):
        vel_msg.linear.x = 2
    if(data == 's'):
        vel_msg.linear.x = -2
    if(data == 'd'):
        vel_msg.angular.z = -2
    if(data == 'a'):
        vel_msg.angular.z = 2
    #rospy.loginfo(msg_str)
    #pub.publish(msg_str)
    velocity_publisher.publish(vel_msg)
    #rate.sleep()

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
HOST = "18.216.189.87"
PORT = 5555
s.connect((HOST, PORT))
while True:
    msg = s.recv(1024)

    if len(msg) > 0:
        print(msg.decode())
        talker(msg.decode())
