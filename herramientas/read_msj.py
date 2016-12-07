#! /usr/bin/python

import socket
from xml.etree.ElementTree import Element, SubElement, Comment, tostring
import datetime
import time


TCP_IP = '0.0.0.0'
host = socket.gethostname()
print "hostname:------->", host

TCP_PORT = 7000
BUFFER_SIZE = 10  # Normally 1024, but we want fast response
MESSAGE = "OK"

#Datos de cabecera
interval='3'
version='4.1(Build 130708)'
agent_name='test_iot'
timezone_offset='0'
address='192.168.1.77'


while 1:
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    s.bind((TCP_IP, TCP_PORT))
    s.listen(2)
    try:
        conn, addr = s.accept()
        print 'Connection address:', addr

        data = conn.recv(BUFFER_SIZE)
        if not data: break
        timestamp='{:%Y-%m-%d %H:%M:%S}'.format(datetime.datetime.now())
        filename='test_iot.'+str(time.time())+'.data'

        agent_data = Element('agent_data',{'description':'','group':'','os_name':'iot','interval':interval,'version':version,'timestamp':timestamp,'agent_name':agent_name,'timezone_offset':timezone_offset, 'address':address})
        comment = Comment('Generated for PyMOTW')
        agent_data.append(comment)

        module=SubElement(agent_data, 'module')
        name=SubElement(module,'name')
        name.text='sacos_de_patata'
        description=SubElement(module,'description')
        description.text='User CPU Usage (%)'
        type_=SubElement(module,'type')
        type_.text='generic_data'
        min_=SubElement(module,'min')
        min_.text='0'
        max_=SubElement(module,'max')
        max_.text='100'
        data_=SubElement(module,'data')
        data_.text=data.rstrip()
        conn.send(MESSAGE)  # echo
        with open('/var/spool/pandora/data_in/'+filename, 'w') as file_:
                file_.write(tostring(agent_data))
        print tostring(agent_data)
        conn.close()
    except:
        print "error_a:"
conn.close()
