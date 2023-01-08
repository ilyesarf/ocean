from ctypes import *
import sys
import time

so_file = '../ocean.so'

ocean = CDLL(so_file)

if __name__ == '__main__':
    st = time.monotonic()
    if len(sys.argv) > 1:
        input = int(sys.argv[1])
    else:
        input = 10

    sockfd = ocean.init_client()

    ocean.send_input(sockfd, input)

    size = ocean.recv_size(sockfd)
    steps = (c_int*size)()

    ocean.recv_steps(sockfd, size, steps)

    ocean.close(sockfd)

    for i in range(size):
        print(steps[i], end = " ")
    
    et = time.monotonic()
    print(f"\nExecution time: {et - st:.6f} seconds")

