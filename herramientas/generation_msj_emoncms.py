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
interval='30'
version='4.1(Build 130708)'
agent_name='San Pablo'
timezone_offset='0'
address='192.168.1.99'


if os.path.isfile('generation_msj.log'):
    os.remove('generation_msj.log')
    with open('generation_msj.log', 'w') as log_:
        log_.write('El fichero de log esta creado de nuevo \n')
else:
    with open('generation_msj.log', 'w') as log_:
        log_.write('inicio de fichero de log \n')


with open('generation_msj.log', 'a') as log_:
    log_.write('Inicio del log :------->' + '\n')


while 1:

    for i in range(999):
        try:
            timestamp='{:%Y-%m-%d %H:%M:%S}'.format(datetime.datetime.now())
            filename='generation_msj.'+str(time.time())+'.data'

            agent_data = Element('agent_data',{'description':'','group':'','os_name':'iot','interval':interval,'version':version,'timestamp':timestamp,'agent_name':agent_name,'timezone_offset':timezone_offset, 'address':address})
            comment = Comment('Generated for PyMOTW')
            agent_data.append(comment)

            module=SubElement(agent_data, 'module')
            name=SubElement(module,'name')
            name.text='temperatura_entrada'
            description=SubElement(module,'description')
            description.text='temperatura de entrada al panel'
            type_=SubElement(module,'type')
            type_.text='generic_data'
            min_=SubElement(module,'min')
            min_.text='0'
            max_=SubElement(module,'max')
            max_.text='999'
            data_=SubElement(module,'data')
            data_.text=str(i)
            with open('/var/spool/pandora/data_in/'+filename, 'w') as file_:
                    file_.write(tostring(agent_data))

            with open('generation_msj.log', 'a') as log_:
                log_.write(tostring(agent_data)+'\n')
            time.sleep(30)
        except:
           with open('generation_msj.log', 'a') as log_:
               log_.write(( 'Error: %s --> '+str(sys.exc_info()[0]) +'\n' ))


