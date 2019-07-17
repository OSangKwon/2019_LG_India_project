import serial
import requests
import socket


ip_addr = '192.168.43.219'
port = 8000

#url = "http://ec2-52-79-243-120.ap-northeast-2.compute.amazonaws.com:3000/python"
print('go')
while True:
    print('test')
    a = input()
    #res = requests.get(url)
    
   # a=res.text
    a=a.encode('utf-8')
    sock.send(a)
