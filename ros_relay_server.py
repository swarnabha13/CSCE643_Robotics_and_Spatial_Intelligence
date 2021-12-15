#!/usr/bin/env python3
import socket
import select
import rospy
from std_msgs.msg import String
from geometry_msgs.msg import Twist

PORT = 5555
HOST = ""
print ("Started server on Port 5555")

def callback(data):
    global clientsocket
    rospy.loginfo(data.data)
    msg = data.data
    clientsocket.send(bytes(msg,"utf-8"))


def listener():
    rospy.init_node('listener', anonymous=True)    
    rospy.Subscriber('cmd_vel', String, callback)
    rospy.spin()


s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind((HOST, PORT))
s.listen(5)
clientsocket, address = s.accept()
print(f"Connection from {address} has been established.")
listener()

