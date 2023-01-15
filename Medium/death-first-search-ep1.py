import sys

# n: the total number of nodes in the level, including the gateways
# l: the number of links
# e: the number of exit gateways
number_of_nodes, number_of_links, number_of_exits = [int(i) for i in input().split()]
links_list = []
gateway_list = []
link_to_remove = [0, 0]
virus_is_nearby = False
gateway_in_danger = 0

for i in range(number_of_links):
    # n1: N1 and N2 defines a link between these nodes
    n1, n2 = [int(j) for j in input().split()]
    links_list.append((n1, n2))

for i in range(number_of_exits):
    ei = int(input())  # the index of a gateway node
    gateway_list.append(ei)


# game loop
while True:
    si = int(input())  # The index of the node on which the Bobnet agent is positioned this turn
    virus_is_nearby = False

    # Get gateway in danger:
    gateway_in_danger = gateway_list[0]
    for i in gateway_list:
        for j in range(number_of_links):
            if i in links_list[j] and si in links_list[j]:
                gateway_in_danger = i
                break

    # Protect the gateway in danger
    for i in range(number_of_links):
        if gateway_in_danger in links_list[i] and si in links_list[i]:
            number_of_links = number_of_links - 1
            link_to_remove = links_list[i]
            links_list.remove(links_list[i])
            virus_is_nearby = True
            break

    # No gateway in danger, but still remove some links around gateways
    if not (virus_is_nearby):
        for i in range(number_of_links):
            if gateway_in_danger in links_list[i]:
                number_of_links -= 1
                link_to_remove = links_list[i]
                links_list.remove(links_list[i])
                break

    print('gateway_in_danger: ', gateway_in_danger, file=sys.stderr, flush=True)
    print('link to remove: ', link_to_remove, file=sys.stderr, flush=True)
    print(link_to_remove[0], link_to_remove[1])
