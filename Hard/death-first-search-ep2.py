import sys


class Node:
    def __init__(self):
        self.node_id = 0
        self.linked_nodes = []
        self.is_exit = False
        self.is_danger_node = False  # A node linked to more than one exit


class NetworkGraph:
    def __init__(self):
        self.nodes_list = []

        # n: the total number of nodes in the level, including the gateways
        # l: the number of links
        # e: the number of exit gateways
        self.nb_nodes, nb_links, nb_exits = [int(i) for i in input().split()]

        for i in range(self.nb_nodes):
            node = Node()
            node.node_id = i
            self.nodes_list.append(node)

        for _ in range(nb_links):
            # n1: N1 and N2 defines a link between these nodes
            n1, n2 = [int(j) for j in input().split()]
            self.nodes_list[n1].linked_nodes.append(n2)
            self.nodes_list[n2].linked_nodes.append(n1)

        # determine if a node is an exit node
        for i in range(nb_exits):
            ei = int(input())  # the index of a gateway node
            self.nodes_list[ei].is_exit = True

        self.update_nodes()

    def _remove_link_between_nodes(self, node_id_1, node_id_2):
        link_to_remove = (node_id_1, node_id_2)
        self.nodes_list[node_id_2].linked_nodes.remove(node_id_1)
        self.nodes_list[node_id_1].linked_nodes.remove(node_id_2)
        return link_to_remove

    def display_network_info(self):
        print("nb_nodes ", self.nb_nodes, file=sys.stderr, flush=True)
        for i in range(self.nb_nodes):
            print(
                "self.nodes_list[i].is_exit",
                self.nodes_list[i].is_exit,
                file=sys.stderr,
                flush=True,
            )
            print(
                "self.nodes_list[i].is_danger_node",
                self.nodes_list[i].is_danger_node,
                file=sys.stderr,
                flush=True,
            )
            print(
                "self.nodes_list[i].linked_nodes",
                self.nodes_list[i].linked_nodes,
                file=sys.stderr,
                flush=True,
            )
            print("...", file=sys.stderr, flush=True)

    def get_link_to_remove(self, bobnet_agent_node):

        link_to_remove = (0, 0)

        # Bobnet agent is one link far from the exit, destroy the link !!!
        for node_id in self.nodes_list[bobnet_agent_node].linked_nodes:
            if self.nodes_list[node_id].is_exit:
                return self._remove_link_between_nodes(bobnet_agent_node, node_id)

        # Bobnet agent is one link close to a danger node, destroy one of its exit links
        for node_id in self.nodes_list[bobnet_agent_node].linked_nodes:
            if self.nodes_list[node_id].is_danger_node:
                for j in self.nodes_list[node_id].linked_nodes:
                    if self.nodes_list[j].is_exit:
                        return self._remove_link_between_nodes(j, node_id)

        # Bobnet is not one link close to a danger node, destroy an exit link of any danger node
        for node in self.nodes_list:
            if node.is_danger_node:
                for node_id in node.linked_nodes:
                    if self.nodes_list[node_id].is_exit:
                        return self._remove_link_between_nodes(node.node_id, node_id)

        # There is no danger node, just destroy any exit link
        for node in self.nodes_list:
            if node.is_exit:
                return self._remove_link_between_nodes(
                    node.node_id, node.linked_nodes[0]
                )

        return link_to_remove

    def update_nodes(self):

        for node in self.nodes_list:
            node.is_danger_node = False
            exit_linked_to_node = 0

            # determine if a node is danger node
            for j in node.linked_nodes:
                if self.nodes_list[j].is_exit:
                    exit_linked_to_node += 1
            if exit_linked_to_node > 1:
                node.is_danger_node = True

            # exit node without links is no longer an exit ;)
            if node.is_exit and len(node.linked_nodes) == 0:
                node.is_exit = False


network = NetworkGraph()
network.display_network_info()

# game loop
while True:
    bobnet_agent_node = int(
        input()
    )  # The index of the node on which the Bobnet agent is positioned this turn
    link_to_remove = network.get_link_to_remove(bobnet_agent_node)
    print(link_to_remove[0], link_to_remove[1])
    network.update_nodes()
