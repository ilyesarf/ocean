#!/usr/bin/env python3

from sys import argv
import time

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
    try:
        n = int(argv[1])
    except:
        n = 10

    steps = collatz(n)
    
    print(steps)

    end = time.monotonic()
    print(f"Execution time: {end-start: .6f} seconds")

