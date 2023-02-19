relation_tree = {}


def get_longest_succession_starting_from_person_x(person_x):
    if person_x not in list(relation_tree.keys()):
        return 1
    else:
        return 1 + max(
            [
                get_longest_succession_starting_from_person_x(i)
                for i in relation_tree[person_x]
            ]
        )


n = int(input())  # the number of relationships of influence
for i in range(n):
    # x: a relationship of influence between two people (x influences y)
    x, y = [int(j) for j in input().split()]
    if x not in relation_tree.keys():
        relation_tree[x] = [y]
    else:
        relation_tree[x].append(y)

successions = [
    get_longest_succession_starting_from_person_x(i) for i in list(relation_tree.keys())
]

# The number of people involved in the longest succession of influences
print(max(successions))
