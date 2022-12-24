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

    n = int(input("n? "))
    print(collatz(n))
