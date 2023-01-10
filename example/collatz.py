#!/usr/bin/env python3

from sys import argv
from ctypes import *
import time
import socket

def collatz(n):
    steps = [n]
    while n != 1:
        if n%2 == 0:
            n //= 2
        else:
            n *= 3
            n += 1

        steps.append(n)
    
    return steps

if __name__ == "__main__":
    start = time.monotonic()    
    ocean = CDLL('../ocean.so')

    sockfd = ocean.init_server()
    print(f"Listening on {sockfd}")

    while True:
        cli_sfd = input = c_int()
        ocean.recv_input(sockfd, byref(cli_sfd), byref(input))

        print(input.value)
        steps = collatz(input.value)
        size = len(steps)

        ocean.send_size(cli_sfd, size)

        for step in steps:
            ocean.send_steps(cli_sfd, step)
        
        
        socket.close(cli_sfd.value)

    socket.close(sockfd)

