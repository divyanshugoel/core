#!/usr/bin/env python
import pika

credentials = pika.PlainCredentials('agv','agv')
parameters = pika.ConnectionParameters('192.168.200.76', 5672, '/',credentials)
connection = pika.BlockingConnection(parameters)
channel = connection.channel()

#channel.queue_declare(queue='hello')
channel.basic_publish(exchange='', routing_key='FMS.RECEIVE-TASK', body='{"taskId":"123","sourceLocation":"IB001-001", "destinationLocation":"MPL003"}')
#channel.basic_publish(exchange='', routing_key='FMS.RECEIVE-TASK', body='{"taskId":"23435124334124","sourceLocation":"IB002-001", "destinationLocation":"TPI001"}')
#channel.basic_publish(exchange='', routing_key='FMS.RECEIVE-TASK', body='{"taskId":"23435124343244","sourceLocation":"IB001-002", "destinationLocation":"TPI001"}')
#channel.basic_publish(exchange='', routing_key='FMS.RECEIVE-TASK', body='{"taskId":"461243323444","sourceLocation":"IB002-003", "destinationLocation":"TPI001"}')
#channel.basic_publish(exchange='', routing_key='FMS.RECEIVE-TASK', body='{"taskId":"354632243323444","sourceLocation":"IB001-002", "destinationLocation":"MPL003"}')
#channel.basic_publish(exchange='', routing_key='FMS.RECEIVE-TASK', body='{"taskId":"23542311243323444","sourceLocation":"IB002-003", "destinationLocation":"MPL004"}')
#channel.basic_publish(exchange='', routing_key='FMS.RECEIVE-TASK', body='{"taskId":"2446311243323444","sourceLocation":"IB002-004", "destinationLocation":"MPL004"}')
#channel.basic_publish(exchange='', routing_key='FMS.RECEIVE-TASK', body='{"taskId":"2343512433442341","sourceLocation":"IB001-004", "destinationLocation":"TPI001"}')
#channel.basic_publish(exchange='', routing_key='FMS.RECEIVE-TASK', body='{"taskId":"2343512433423442","sourceLocation":"IB002-001", "destinationLocation":"TPI001"}')
#channel.basic_publish(exchange='', routing_key='FMS.RECEIVE-TASK', body='{"taskId":"2343512423443","sourceLocation":"IB001-002", "destinationLocation":"TPI001"}')
#channel.basic_publish(exchange='', routing_key='FMS.RECEIVE-TASK', body='{"taskId":"4612433423444","sourceLocation":"IB002-003", "destinationLocation":"TPI001"}')
#channel.basic_publish(exchange='', routing_key='FMS.RECEIVE-TASK', body='{"taskId":"3546322433445","sourceLocation":"IB001-002", "destinationLocation":"MPL003"}')
#channel.basic_publish(exchange='', routing_key='FMS.RECEIVE-TASK', body='{"taskId":"2354231124234334466","sourceLocation":"IB002-003", "destinationLocation":"MPL004"}')
#channel.basic_publish(exchange='', routing_key='FMS.RECEIVE-TASK', body='{"taskId":"244631124332344455","sourceLocation":"IB002-004", "destinationLocation":"MPL004"}')
#channel.basic_publish(exchange='', routing_key='FMS.RECEIVE-TASK', body='{"taskId":"234351244323411","sourceLocation":"IB001-002", "destinationLocation":"TPI001"}')
#channel.basic_publish(exchange='', routing_key='FMS.RECEIVE-TASK', body='{"taskId":"461243344423412","sourceLocation":"IB002-003", "destinationLocation":"TPI001"}')
#channel.basic_publish(exchange='', routing_key='FMS.RECEIVE-TASK', body='{"taskId":"354632243344523413","sourceLocation":"IB001-002", "destinationLocation":"MPL003"}')
#channel.basic_publish(exchange='', routing_key='FMS.RECEIVE-TASK', body='{"taskId":"235423112433446632414","sourceLocation":"IB002-003", "destinationLocation":"MPL004"}')
#channel.basic_publish(exchange='', routing_key='FMS.RECEIVE-TASK', body='{"taskId":"235423112433324446632414","sourceLocation":"IB002-003", "destinationLocation":"MPL003"}')
#channel.basic_publish(exchange='', routing_key='FMS.RECEIVE-TASK', body='{"taskId":"235423112433442343246623414","sourceLocation":"IB002-003", "destinationLocation":"MPL003"}')

# channel.basic_publish(exchange='', routing_key='FMS.RECEIVE-TASK', body='{"taskId":"TASK0009","sourceLocation":"IB001-006", "destinationLocation":"OPL001"}')
# channel.basic_publish(exchange='', routing_key='FMS.RECEIVE-TASK', body='{"taskId":"TASK0000","sourceLocation":"IB007-003", "destinationLocation":"SPI001"}')  
# channel.basic_publish(exchange='', routing_key='FMS.RECEIVE-TASK', body='{"taskId":"TASK00011","sourceLocation":"IB007-002", "destinationLocation":"IB001-006"}')    
# channel.basic_publish(exchange='', routing_key='FMS.RECEIVE-TASK', body='{"taskId":"TASK00014","sourceLocation":"MPL003", "destinationLocation":"PCL001"}')                                                                   
# channel.basic_publish(exchange='', routing_key='FMS.RECEIVE-TASK', body='{"taskId":"TASK0028","sourceLocation":"OPL003", "destinationLocation":"IB001-003"}')  
# channel.basic_publish(exchange='', routing_key='FMS.RECEIVE-TASK', body='{"taskId":"TASK0029","sourceLocation":"IB001-006", "destinationLocation":"OPL001"}')
# channel.basic_publish(exchange='', routing_key='FMS.RECEIVE-TASK', body='{"taskId":"TASK0020","sourceLocation":"IB007-003", "destinationLocation":"SPI001"}')  
# channel.basic_publish(exchange='', routing_key='FMS.RECEIVE-TASK', body='{"taskId":"TASK00021","sourceLocation":"IB007-002", "destinationLocation":"IB001-006"}')    
# channel.basic_publish(exchange='', routing_key='FMS.RECEIVE-TASK', body='{"taskId":"TASK00024","sourceLocation":"MPL003", "destinationLocation":"PCL001"}')                                                                              
                    
print("Successful")

connection.close()
