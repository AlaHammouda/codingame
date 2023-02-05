# w: width of the building.
# h: height of the building.
w, h = [int(i) for i in input().split()]
n = int(input())  # maximum number of turns before game over.
x0, y0 = [int(i) for i in input().split()]

phase = -1
oldpos = [x0, y0]
newpos = [x0, y0]
minpos = [0, 0]
maxpos = [w - 1, h - 1]
dimension = [w - 1, h - 1]

# game loop
while True:
    # Current distance to the bomb compared to previous distance (COLDER, WARMER, SAME or UNKNOWN)
    bomb_dir = input()

    if phase < 0:
        if phase == -1 and w >= 2:
            phase = 0
        else:
            phase = 1
        newpos[phase] = minpos[phase] + maxpos[phase] - oldpos[phase]
        # i.e. average of newpos + oldpos = average of minpos + maxpos
    else:
        old, new = oldpos[phase], newpos[phase]
        remainder = (old + new) % 2
        middle = (old + new) // 2
        oldpos[phase] = new
        if bomb_dir == "SAME":
            newpos[phase] = middle
            if phase == 0:
                phase = -2
        else:
            if bomb_dir == "WARMER":
                if old < new:
                    minpos[phase] = max(minpos[phase], middle + 1)
                elif old > new:
                    maxpos[phase] = min(maxpos[phase], middle - 1 * (remainder == 0))
            elif bomb_dir == "COLDER":
                if old > new:
                    minpos[phase] = max(minpos[phase], middle + 1)
                elif old < new:
                    maxpos[phase] = min(maxpos[phase], middle - 1 * (remainder == 0))
            if minpos[phase] == maxpos[phase]:
                newpos[phase] = minpos[phase]
                if phase == 0:
                    phase = 1
            tentative = minpos[phase] + maxpos[phase] - new
            if tentative < 0 or tentative > dimension[phase]:
                tentative = (minpos[phase] + maxpos[phase]) // 2
            if tentative == new or tentative == old or maxpos[phase] - minpos[phase] <= 2:
                for i in range(minpos[phase], maxpos[phase] + 1):
                    if i != new and i != old:
                        tentative = i
                        break
            newpos[phase] = tentative

    # the location of the next window Batman should jump to.
    print(newpos[0], newpos[1])
