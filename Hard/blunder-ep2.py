room_list = []


def maximum_amount_of_money(room_number=0):
    if processed_rooms[room_number][0] == 1:
        return processed_rooms[room_number][1:][0]
    elif room_list[room_number][2] == "E" and room_list[room_number][3] == "E":
        result = int(room_list[room_number][1])
        processed_rooms[room_number] = [1]
        processed_rooms[room_number] += [result]
        return result
    elif room_list[room_number][2] == "E":
        result = int(room_list[room_number][1]) + maximum_amount_of_money(
            int(room_list[room_number][3])
        )
        processed_rooms[room_number] = [1]
        processed_rooms[room_number] += [result]
        return result
    elif room_list[room_number][3] == "E":
        result = int(room_list[room_number][1]) + maximum_amount_of_money(
            int(room_list[room_number][2])
        )
        processed_rooms[room_number] = [1]
        processed_rooms[room_number] += [result]
        return result
    else:
        result = int(room_list[room_number][1]) + max(
            maximum_amount_of_money(int(room_list[room_number][2])),
            maximum_amount_of_money(int(room_list[room_number][3])),
        )
        processed_rooms[room_number] = [1]
        processed_rooms[room_number] += [result]
        return result


n = int(input())
processed_rooms = [
    [-1] for i in range(n)
]  # -1: not processed  1: processed, Don't process again (memozation)

for i in range(n):
    room = input()
    room_list.append(room.split(" "))

print(maximum_amount_of_money())
