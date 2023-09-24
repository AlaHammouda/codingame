import math
from datetime import datetime


class ParkedVehicle:
    entree_time: datetime
    vehicle_id: str


total_fees = 0
cars_not_parked = 0
motorbikes_not_parked = 0
parked_vehicles = []
MAXIMUM_CAR_PLACES = 7
MAXIMUM_MOTOBIKE_PLACES = 2
nb_parked_cars = 0
nb_parked_motobikes = 0

h = int(input())

for i in range(h):
    row_data = input().split(" ")
    if row_data[1] == ">":
        for vehicle in row_data[2:]:
            if (vehicle[0] == "C" and nb_parked_cars < MAXIMUM_CAR_PLACES) or (
                vehicle[0] == "M" and nb_parked_motobikes < MAXIMUM_MOTOBIKE_PLACES
            ):
                new_vehicle = ParkedVehicle()
                new_vehicle.entree_time = datetime.strptime(row_data[0], "%H:%M")
                new_vehicle.vehicle_id = vehicle
                parked_vehicles.append(new_vehicle)
                if vehicle[0] == "C":
                    nb_parked_cars += 1
                else:
                    nb_parked_motobikes += 1
            else:
                if vehicle[0] == "C":
                    cars_not_parked += 1
                else:
                    motorbikes_not_parked += 1
    else:
        for vehicle in row_data[2:]:
            for parked_vehicle in parked_vehicles:
                if vehicle == parked_vehicle.vehicle_id:
                    parking_duration_minutes = (
                        datetime.strptime(row_data[0], "%H:%M")
                        - parked_vehicle.entree_time
                    ).total_seconds() / 60
                    if parked_vehicle.vehicle_id[0] == "C":
                        if parking_duration_minutes >= 30:
                            total_fees += math.ceil(parking_duration_minutes / 15) * 1.2
                        nb_parked_cars -= 1
                    else:
                        if parking_duration_minutes >= 30:
                            total_fees += math.ceil(parking_duration_minutes / 15) * 0.7
                        nb_parked_motobikes -= 1

                    parked_vehicles.remove(parked_vehicle)

total_fees += len(parked_vehicles) * 30

print("{:.1f}".format(total_fees), cars_not_parked, motorbikes_not_parked)
