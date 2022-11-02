import random
import json

points = [
    (48.5166707, -71.6375025), # Alpha
    (48.5060947, -71.6317518), # Bravo
    (48.4921159, -71.6340069), # Charlie
    (48.5150341, -71.6404442), # Delta
    (48.5005337, -71.6782955), # Echo
    (48.5088395, -71.6040591), # Foxtrot
    (48.5101473, -71.6522101), # Golf
    (48.5129917, -71.6426006), # Hotel
    (48.5117408, -71.6428152), # India
    (48.5193311, -71.6229056), # Juliette
    (48.4984623, -71.6568088), # Kilo
    (48.5019885, -71.6253089), # Lima
    (48.520525, -71.6720008),  # Mike
    (48.5090567, -71.6461702), # November
    (48.5107057, -71.6516848), # Oscar
    (48.5039667, -71.6298198), # Papa
    (48.5262308, -71.6345802), # Quebec
    (48.511563, -71.6804996),  # Point 18
    (48.4984266, -71.6425625), # Romeo
    (48.5258329, -71.6320911), # Sierra
    (48.4996779, -71.6758648), # Tango
    (48.4937058, -71.6290012), # Uniform
    (48.510353, -71.6228085),  # Victor
    (48.5093153, -71.6216069), # Whiskey
    (48.4969248, -71.6034018), # Xray
    (48.5112557, -71.6312968), # Yankee
    (48.4932846, -71.6664874)  # Zulu
]

start_point = (48.50799131904116, -71.63956962892846)
route_count = 15

routes = []
for i in range(route_count):
    start = random.randint(0, len(points)-1)
    end = random.randint(0, len(points)-1)
    while end == start:
        end = random.randint(0, len(points)-1)
    routes.append({
        "start": points[start],
        "end": points[end],
        "revenue": random.randint(10, 500)
    })

with open("problem.json", "w") as f:
    json.dump({
        "start_point": start_point,
        "routes": routes
    }, f, indent=4)
