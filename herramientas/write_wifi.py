#!/usr/bin/env python

import socket
import time


TCP_IP = '192.168.1.128'
TCP_PORT = 80
BUFFER_SIZE = 1024
MESSAGE = "este es el mensaje numero -> %d!"

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((TCP_IP, TCP_PORT))
for i in range(100):
    s.send(MESSAGE %(i))
    data = s.recv(BUFFER_SIZE)
    print "received data:", data
    time.sleep(1)
s.close()