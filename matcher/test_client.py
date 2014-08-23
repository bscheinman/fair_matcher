#!/usr/bin/python

import socket

sock = socket.socket()
sock.connect(('localhost', 2468))

message = '\x08\x00\x00\x00\x00\x00\x01\x00abcdefgh'
sock.send(message)

raw_input()

sock.send('\x10\x00\x00\x00\x00\x00\x01\x00qwertyuiopasdfgh')

sock.close()

