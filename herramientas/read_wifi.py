#! /usr/bin/python

import socket


TCP_IP = '192.168.1.128'

host = socket.gethostname()
print "hostname:------->", host

TCP_PORT = 7000
BUFFER_SIZE = 1024  # Normally 1024, but we want fast response
MESSAGE = "OK"

while 1:
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    s.bind((TCP_IP, TCP_PORT))
    s.listen(2)

    conn, addr = s.accept()
    print 'Connection address:', addr
    while 1:
        data = conn.recv(BUFFER_SIZE)
        if not data: break
        print "received data:", data
        conn.send(MESSAGE)  # echo
    conn.close()
conn.close()


