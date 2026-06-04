while True:
    factors = [1]
    num = int(input("choose a number to reduce into factors:"))
    factor = 2
    while num != 1:
        if num % factor == 0:
            num = int(num / factor)
            factors.append(factor)
        else: factor = factor + 1
    print(factors)