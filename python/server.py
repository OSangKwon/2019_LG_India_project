import serial
import requests
import socket


ip_addr = '192.168.137.238'
port = 8000

server_socket = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
server_socket.bind((ip_addr,port))
server_socket.listen(1)
sock, addr = server_socket.accept()
url = "http://ec2-52-79-243-120.ap-northeast-2.compute.amazonaws.com:3000/python"
while True:
    res = requests.get(url)
    a=res.text
    print(a)
    a=a.encode('utf-8')
    sock.send(a);
