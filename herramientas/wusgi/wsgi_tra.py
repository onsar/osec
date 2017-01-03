import os.path
import sys
from cgi import parse_qs, escape

from xml.etree.ElementTree import Element, SubElement, Comment, tostring
import datetime
import time

# Valores
version='4.1(Build 130708)'
agent_name='San Pablo'
timezone_offset='0'
address='192.168.1.99'
interval='60'


def application(env, start_response):

    #Parseo
    try:
        request_body_size = int(env.get('CONTENT_LENGTH', 0))
    except (ValueError):
        request_body_size = 0
    start_response('200 OK', [('Content-Type','text/html')])

    request_body = env['wsgi.input'].read(request_body_size)
    d = parse_qs(request_body)

    # campos a mapear en el fichero para Pandora
    name_r = d.get('name', [''])[0]    
    value_r = d.get('value', [''])[0]
    # agent_name = d.get('site', [''])[0]
    # description_r = d.get('description', [''])[0]
    

    #construir xml
    try:
        timestamp='{:%Y-%m-%d %H:%M:%S}'.format(datetime.datetime.now())
        filename='temperatura.'+str(time.time())+'.data'

        agent_data = Element('agent_data',{'description':'','group':'','os_name':'iot','interval':interval,'version':version,'timestamp':timestamp,'agent_name':agent_name,'timezone_offset':timezone_offset, 'address':address})
        
        comment = Comment('Generated for PyMOTW')
        agent_data.append(comment)

        module=SubElement(agent_data, 'module')
        
        name_=SubElement(module,'name')
        # name.text='temperatura_entrada'
        name_.text=str(name_r)
        
        description_=SubElement(module,'description')
        description_.text='Sensor de temperatura'
        # description_.text=str(description_r)
        
        type_=SubElement(module,'type')
        type_.text='generic_data'
        
        min_=SubElement(module,'min')
        min_.text='0'
        
        max_=SubElement(module,'max')
        max_.text='0'
        
        data_=SubElement(module,'data')
        data_.text=str(value_r)
        
        
        with open('/home/onsar/prueba_basic/generated_files/'+filename, 'w') as file_:
            file_.write(tostring(agent_data))
    except:
        with open('generation_msj.log', 'a') as log_:
            log_.write(( 'Error: %s --> '+str(sys.exc_info()[0]) +'\n' ))



    return [b"APP_OK"]
