from re import findall
from copy import deepcopy


def parse_line(line):
    return findall('sw|se|nw|ne|e|w', line)


def count_black_hexagons(hexagons):
    result = 0
    for value in hexagons.values():
        if value:
            result += 1
    return result


def get_bounds(hexagons):
    max_x, max_y, min_x, min_y = 0, 0, 0, 0
    for hexagon in hexagons:
        if hexagon[0] > max_x:
            max_x = hexagon[0]
        if hexagon[1] > max_y:
            max_y = hexagon[1]
        if hexagon[0] < min_x:
            min_x = hexagon[0]
        if hexagon[1] < min_y:
            min_y = hexagon[1]
    return max_x, max_y, min_x, min_y


def part_one(lines):
    hexagons = {(0, 0): False}
    pathing = {"nw": (-1, 1), "w": (-1, 0), "sw": (0, -1),
               "ne": (0, 1), "e": (1, 0), "se": (1, -1)}
    for line in lines:
        directions = parse_line(line)
        c_hexagon = (0, 0)
        for direction in directions:
            path = pathing[direction]
            c_hexagon = (c_hexagon[0] + path[0], c_hexagon[1] + path[1])
        if c_hexagon in hexagons:
            hexagons[c_hexagon] = not hexagons[c_hexagon]
        else:
            hexagons[c_hexagon] = True  # start black
    return count_black_hexagons(hexagons), hexagons


def part_two(lines):
    _, hexagons = part_one(lines)
    combinations = [(-1, 1), (-1, 0), (0, -1),
                    (0, 1), (1, 0), (1, -1)]
    max_x, max_y, min_x, min_y = get_bounds(hexagons)
    new_hexagons = deepcopy(hexagons)
    for _ in range(100):
        for x in range(min_x - 1, max_x + 2):
            for y in range(min_y - 1, max_y + 2):
                count = 0
                hexagon = (x, y)
                for c in combinations:
                    adj_hexagon = (hexagon[0] + c[0], hexagon[1] + c[1])
                    if adj_hexagon in hexagons and hexagons[adj_hexagon]:
                        count += 1
                if count == 0 or count > 2:
                    new_hexagons[hexagon] = False
                elif count == 2:
                    new_hexagons[hexagon] = True
        hexagons = deepcopy(new_hexagons)
        max_x, max_y, min_x, min_y = get_bounds(hexagons)
    return count_black_hexagons(hexagons)


with open("input.txt") as f:
    lines = f.read().splitlines()
    print(part_one(lines)[0])
    print(part_two(lines))
