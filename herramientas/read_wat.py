#! /usr/bin/python

# Para la lectura de mensajes desde arduino
# w=wireless
# a=arduino
# t=temperatura

import socket
import os.path
import sys

# TCP_IP = '0.0.0.0'
TCP_IP = '192.168.1.128'

if os.path.isfile('read_wat.log'):
    os.remove('read_wat.log')
    with open('read_wat.log', 'w') as log_:
        log_.write('El fichero de log esta creado de nuevo \n')
else:
    with open('read_wat.log', 'w') as log_:
        log_.write('inicio de fichero de log \n')
        

host = socket.gethostname()
# print "hostname:------->", host

with open('read_wat.log', 'a') as log_:
    log_.write('hostname:------->' + host + '\n')

TCP_PORT = 8000
BUFFER_SIZE = 1024  # Normally 1024, but we want fast response
MESSAGE = "OK"

while 1:
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    s.bind((TCP_IP, TCP_PORT))
    s.listen(2)
    try:
        conn, addr = s.accept()
    
        # print 'Connection address:', addr
        with open('read_wat.log', 'a') as log_:
            log_.write('Connection address:' + str(addr)+'\n')
        
        
        while 1:
            data = conn.recv(BUFFER_SIZE)
            if not data: break
            # print "received data:", data
            with open('read_wat.log', 'a') as log_:
                log_.write('received data:'+ str(data) + '\n')

            conn.send(MESSAGE)  # echo
        conn.close()
        
    except:
        with open('read_wt.log', 'a') as log_:
            log_.write(( 'Error: %s --> '+str(sys.exc_info()[0]) +'\n' ))
conn.close()


