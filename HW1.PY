import random
import time


def bit_string(k):
    return ''.join(random.choice(['0', '1']) for _ in range(k))


def string_xor(a, b, index=0):
    if index + len(b) > len(a):
        return a

    a = list(a)
    for i in range(len(b)):
        a[index + i] = '1' if a[index + i] != b[i] else '0'

    return ''.join(a)


def find_remainder(dividend, divisor):
    dividend = list(dividend)
    divisor_len = len(divisor)

    for i in range(len(dividend)):
        if i + divisor_len <= len(dividend):
            if dividend[i] == '1':
                for j in range(divisor_len):
                    dividend[i + j] = (
                        '1' if dividend[i + j] != divisor[j] else '0'
                    )
        else:
            break

    # remainder is last (len(divisor)-1) bits
    return ''.join(dividend[-(divisor_len - 1):])


def find_crc(message, polynomial):
    message = message + '0' * (len(polynomial) - 1)
    return find_remainder(message, polynomial)


def find_fcs(message, polynomial):
    return message + find_crc(message, polynomial)


def add_errors(t, error_prob=10):
    t = list(t)
    for i in range(len(t)):
        if random.randint(0, error_prob - 1) == 0:
            t[i] = '1' if t[i] == '0' else '0'
    return ''.join(t)


def check_valid(t, p):
    print(f"\nChecking validity of {t} with respect to {p}...")
    remainder = find_remainder(t, p)

    if '1' in remainder:
        print(f"Non-zero remainder: {remainder}")
        print("Invalid! It should be discarded.")
        return False

    print("Valid! It should be accepted.")
    return True


def q1_original():
    n = 10
    k = 6

    while True:
        t = input("\nDo you want to give custom input (n and k)? [y/n]\n")

        if len(t) != 1:
            print("Please only enter 'y' or 'n'")
        elif t == 'y':
            n = int(input("Enter the value of integer n (frame size): "))
            k = int(input("Enter the value of integer k (message size): "))

            if n - k + 1 <= 0:
                print("n should be greater than or equal to k")
                n = 10
                k = 6
                continue
            else:
                break
        elif t == 'n':
            print("\nProceeding with default values n=10 and k=6...\n")
            break
        else:
            print("Please only enter 'y' or 'n'")

    print("First input:")
    m = bit_string(k)
    p = "0"
    while p[0] != '1':
        p = bit_string(n - k + 1)

    crc = find_crc(m, p)

    print(f"M = {m}, P = {p}")
    print(f"CRC = {crc}")
    print(f"FCS = {m + crc}")
    check_valid(m + crc, p)

    print("\nSecond input:")
    m = bit_string(k)
    p = "0"
    while p[0] != '1':
        p = bit_string(n - k + 1)

    crc = find_crc(m, p)

    print(f"M = {m}, P = {p}")
    print(f"CRC = {crc}")
    print(f"FCS = {m + crc}")
    check_valid(m + crc, p)


def q1_modified():
    n = 15
    k = 10

    m = bit_string(k)
    p = "110101"

    t = find_fcs(m, p)

    print(f"\nMessage: {m}, Polynomial: {p}")
    print("Transmission frame (T):")
    print(t)

    t = add_errors(t)

    print("\nTransmission frame after introducing errors:")
    print(t)

    check_valid(t, p)


def main():
    random.seed(time.time())

    while True:
        print("\nThis program can be used in two ways:")
        print("(1) Generate CRC from two random strings")
        print("(2) Generate a 15-bit frame, introduce some errors, and check validity")

        s = input()

        if len(s) != 1:
            print("Please write only 1 or 2.")
        elif s == '1':
            q1_original()
            break
        elif s == '2':
            q1_modified()
            break
        else:
            print("Please write only 1 or 2.")

    print()


if __name__ == "__main__":
    main()