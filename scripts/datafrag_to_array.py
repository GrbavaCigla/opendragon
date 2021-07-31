from sys import argv, exit

if len(argv) != 2:
    print("Usage:", argv[0], "datafrag")
    exit(1)

array = [argv[1][i - 1] + argv[1][i] for i in range(1, len(argv[1]), 2)]

formatted = "unsigned char data[] = {0x" + ", 0x".join(array) + "};"
print(formatted)

