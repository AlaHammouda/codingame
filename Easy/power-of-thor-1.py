# light_x: the X position of the light of power
# light_y: the Y position of the light of power
# initial_tx: Thor's starting X position
# initial_ty: Thor's starting Y position
light_x, light_y, initial_tx, initial_ty = [int(i) for i in input().split()]
current_x = initial_tx
current_y = initial_ty
next_move_on_x = 0
next_move_on_y = 0


# game loop
while True:
    remaining_turns = int(input())  # The remaining amount of turns Thor can move.
    if current_x < light_x:
        next_move_on_x = 1
    elif current_x > light_x:
        next_move_on_x = -1
    else:
        next_move_on_x = 0

    if current_y < light_y:
        next_move_on_y = 1
    elif current_y > light_y:
        next_move_on_y = -1
    else:
        next_move_on_y = 0

    if next_move_on_x == 1 and next_move_on_y == 1:
        print('SE')
    elif next_move_on_x == -1 and next_move_on_y == -1:
        print('NW')
    elif next_move_on_x == 1 and next_move_on_y == -1:
        print('NE')
    elif next_move_on_x == -1 and next_move_on_y == 1:
        print('SW')
    elif next_move_on_x == 1 and next_move_on_y == 0:
        print('E')
    elif next_move_on_x == 0 and next_move_on_y == 1:
        print('S')
    elif next_move_on_x == -1 and next_move_on_y == 0:
        print('W')
    elif next_move_on_x == 0 and next_move_on_y == -1:
        print('N')
    else:
        print('error')

    current_x += next_move_on_x
    current_y += next_move_on_y
