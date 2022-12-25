#!/usr/bin/env python3

from sys import argv

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
    
    try:
        n = int(argv[1])
    except:
        n = int(input('n? '))

    steps = collatz(n)

    print((n, len(steps)))
    print(steps)
