from cs50 import get_int
import sys

def is_visa(n):
    if n == 4:
        return True
    return False

def is_master(n):
    if n == 51 or n == 52 or n == 53 or n == 54 or n == 55:
        return True
    return False

def is_amex(n):
    if n == 34 or n == 37:
        return True
    return False

def sum123(n):
    if n < 10:
        return n

    s = 0
    while n > 0:
        s = s + n % 10
        n = n // 10

    return s

def check(n):
    sum1 = 0
    sum2 = 0
    turn = 0
    aux = n
    count = 0

    while aux > 0:
        if turn == 0:
            turn = 1
            sum2 = sum2 + aux % 10
        elif turn == 1:
            turn = 0
            db = aux % 10
            sum1 += sum123(db * 2)

        aux = aux // 10
        count += 1


    sum1 = int(sum1)

    if (sum1 + sum2) % 10 != 0:
        print("INVALID")
        sys.exit()

    while n > 1:
        if n < 100:
            if is_master(n) == True and count == 16:
                print('MASTERCARD')
                sys.exit()
            elif is_visa(n) == True and (count == 13 or count == 16):
                print('VISA')
                sys.exit()
            elif is_amex(n) == True and count == 15:
                print("AMEX")
                sys.exit()

        n = n//10
        n = int(n)

    print("INVALID")

while True:
    x = get_int("Number: ");
    temp = str(x)
    if len(temp) > 0 and len(temp) <= 16:
        break

check(x)
