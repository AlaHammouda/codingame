import sys
import math
from collections import deque


class TanStation:
    station_id: str
    station_name: str
    latitude: float
    longitude: float


class TanRoute:
    start_station_id: str
    end_station_id: str


class TanNetwork:
    def __init__(self):
        self.nb_stops = int(input())
        self.stops = {}
        for i in range(self.nb_stops):
            stop_data = input().split(",")
            stop = TanStation()
            stop.station_id = stop_data[0].split(":")[1]
            stop.station_name = stop_data[1]
            stop.latitude = float(stop_data[3])
            stop.longitude = float(stop_data[4])
            self.stops[stop.station_id] = stop

        self.nb_routes = int(input())
        self.routes = []
        for i in range(self.nb_routes):
            route_data = input().split(" ")
            route = TanRoute()
            route.start_station_id = route_data[0].split(":")[1]
            route.end_station_id = route_data[1].split(":")[1]
            self.routes.append(route)

    def calculate_distance_between_two_points(self, start_station, end_station):
        x = (end_station.longitude - start_station.longitude) * math.cos(
            (end_station.latitude + start_station.latitude) / 2
        )
        y = end_station.latitude - start_station.latitude
        distance = math.sqrt(x**2 + y**2) * 6371
        return distance

    # Get the shortest path using Dijikstra algorithme
    def get_shortest_path(self, start_stop_id, end_stop_id):
        distances = {stop.station_id: float("inf") for stop in self.stops.values()}
        distances[start_stop_id] = 0
        previous_stops = {stop.station_id: None for stop in self.stops.values()}

        if start_stop_id == end_stop_id:
            return [self.stops[start_stop_id].station_name]

        queue = deque([start_stop_id])
        while queue:
            current_stop_id = queue.popleft()
            for route in self.routes:
                if route.start_station_id == current_stop_id:
                    distance = distances[
                        current_stop_id
                    ] + self.calculate_distance_between_two_points(
                        self.stops[current_stop_id], self.stops[route.end_station_id]
                    )
                    if distance < distances[route.end_station_id]:
                        distances[route.end_station_id] = distance
                        previous_stops[route.end_station_id] = current_stop_id
                        queue.append(route.end_station_id)

        path = []
        if previous_stops[end_stop_id] is None:
            return "IMPOSSIBLE"
        else:
            current_stop = end_stop_id
            while current_stop is not None:
                path.insert(0, self.stops[current_stop].station_name)
                current_stop = previous_stops[current_stop]
            return path

    # For debugging purposes
    def display_stop_and_routes(self):
        print("stops: \n", file=sys.stderr, flush=True)
        for i in self.stops.keys():
            print("station id: ", self.stops[i].station_id, file=sys.stderr, flush=True)
            print(
                "station_name: ",
                self.stops[i].station_name,
                file=sys.stderr,
                flush=True,
            )
            print("latitude: ", self.stops[i].latitude, file=sys.stderr, flush=True)
            print(
                "longitude: ",
                self.stops[i].longitude,
                "\n",
                file=sys.stderr,
                flush=True,
            )

        print("routes: \n", file=sys.stderr, flush=True)
        for i in range(self.nb_routes):
            print(
                "start_station: ",
                self.routes[i].start_station_id,
                file=sys.stderr,
                flush=True,
            )
            print(
                "end_station: ",
                self.routes[i].end_station_id,
                "\n",
                file=sys.stderr,
                flush=True,
            )


start_point = input().split(":")[1]
end_point = input().split(":")[1]

tan_network = TanNetwork()
# tan_network.display_stop_and_routes()
path = tan_network.get_shortest_path(start_point, end_point)
print("calculated path: \n", path, file=sys.stderr, flush=True)
if path != "IMPOSSIBLE":
    for i in path:
        print(i.strip('"'))
else:
    print("IMPOSSIBLE")
