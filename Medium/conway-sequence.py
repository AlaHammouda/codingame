import sys

R = int(input())
L = int(input())

result = str(R)
next_result = ""
redondance = 1

for j in range(L - 1):
    line = result.strip().split(" ")
    print(result, file=sys.stderr, flush=True)
    next_result = ""
    while len(line) > 1:
        if len(line) == 2 and line[0] == line[1]:
            redondance += 1
            next_result += str(redondance) + " " + str(line[0]) + " "
            redondance = 1
        elif len(line) == 2 and line[0] != line[1]:
            next_result += str(redondance) + " " + str(line[0]) + " "
            next_result += "1 " + str(line[1]) + " "
            redondance = 1
        elif line[0] == line[1]:
            redondance += 1
        else:
            next_result += str(redondance) + " " + str(line[0]) + " "
            redondance = 1

        line = line[1:]

    if next_result == "":
        next_result = "1 " + str(line[0])

    result = next_result

print(result.strip())
