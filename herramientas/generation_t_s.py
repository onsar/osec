#! /usr/bin/python
# Genera un xml con formato pandora

import socket
from xml.etree.ElementTree import Element, SubElement, Comment, tostring
import datetime
import time

import os.path
import sys


TCP_IP = '0.0.0.0'

# TCP_PORT = 7000
# BUFFER_SIZE = 10  # Normally 1024, but we want fast response
# MESSAGE = "OK"

#Datos de cabecera
interval='60'
version='4.1(Build 130708)'
agent_name='San Pablo'
timezone_offset='0'
address='192.168.1.99'


if os.path.isfile('generation_t_s.log'):
    os.remove('generation_t_s.log')
    with open('generation_t_s.log', 'w') as log_:
        log_.write('El fichero de log esta creado de nuevo \n')
else:
    with open('generation_t_s.log', 'w') as log_:
        log_.write('inicio de fichero de log \n')


with open('generation_t_s.log', 'a') as log_:
    log_.write('Inicio del log :------->' + '\n')


while 1:

    for i in range(20,99):
        try:
            timestamp='{:%Y-%m-%d %H:%M:%S}'.format(datetime.datetime.now())
            filename='generation_t_s.'+str(time.time())+'.data'

            agent_data = Element('agent_data',{'description':'','group':'','os_name':'iot','interval':interval,'version':version,'timestamp':timestamp,'agent_name':agent_name,'timezone_offset':timezone_offset, 'address':address})
            comment = Comment('Generated for PyMOTW')
            agent_data.append(comment)

            module=SubElement(agent_data, 'module')
            name=SubElement(module,'name')
            name.text='temperatura_salida'
            description=SubElement(module,'description')
            description.text='temperatura de salida del panel'
            type_=SubElement(module,'type')
            type_.text='generic_data'
            min_=SubElement(module,'min')
            min_.text='0'
            max_=SubElement(module,'max')
            max_.text='900'
            data_=SubElement(module,'data')
            data_.text=str(i*10)
            with open('/var/spool/pandora/data_in/'+filename, 'w') as file_:
                    file_.write(tostring(agent_data))

            with open('generation_t_s.log', 'a') as log_:
                log_.write(tostring(agent_data)+'\n')
            time.sleep(60)
        except:
           with open('generation_t_s.log', 'a') as log_:
               log_.write(( 'Error: %s --> '+str(sys.exc_info()[0]) +'\n' ))


