#!/usr/bin/env python

import socket
import time


# TCP_IP = '192.168.1.128'
TCP_IP = '192.168.1.130'
TCP_PORT = 2121
BUFFER_SIZE = 1024
MESSAGE = "%d"
# MESSAGE = "este es el mensaje numero -> %d!"

# s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
while 1:
    for i in range(100):
        try:
            print(i)
            s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            s.connect((TCP_IP, TCP_PORT))
            time.sleep(1)
            s.send(MESSAGE %(i))
            # data = s.recv(BUFFER_SIZE)
            # print "received data:", data
            time.sleep(1)
            print("bucle -----1")
            # s.shutdown() 
            print("bucle -----2")
            s.close()
            print("bucle -----3")
            time.sleep(2)
            
        except:
            try:
                print("Error_1")
                # s.shutdown(SHUT_RDWR) 
                s.close()
                time.sleep(2)
            except:
                print("Error_2")
        print("bucle_4")
        time.sleep(2)
    # time.sleep(2)
    # try:
        # s.shutdown(SHUT_RDWR)
        # s.close()
    # except:
        # print("Error_2")
    # time.sleep(2)