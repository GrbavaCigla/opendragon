#!/usr/bin/env python3
from sys import argv, exit

if len(argv) < 2:
    print("Usage:", argv[0], "datafrag")
    exit(1)

inp = "".join(argv[1:])

array = [inp[i - 1] + inp[i] for i in range(1, len(inp), 2)]

formatted = "unsigned char data[] = {0x" + ", 0x".join(array) + "};"
print(formatted)
