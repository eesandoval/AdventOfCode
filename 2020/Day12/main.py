def rotate(direction, degrees):
    direction = direction + degrees
    direction = direction % 360
    if direction < 0:
        return direction + 360
    return direction


def move(position, direction, value):
    if direction == 0:
        return (position[0], position[1] + value)
    elif direction == 90:
        return (position[0] + value, position[1])
    elif direction == 180:
        return (position[0], position[1] - value)
    elif direction == 270:
        return (position[0] - value, position[1])


def part_one(lines):
    direction = 90
    position = (0, 0)
    for line in lines:
        value = int(line[1:])
        if line[0] == 'F':
            position = move(position, direction, value)
        elif line[0] == 'N':
            position = move(position, 0, value)
        elif line[0] == 'E':
            position = move(position, 90, value)
        elif line[0] == 'S':
            position = move(position, 180, value)
        elif line[0] == 'W':
            position = move(position, 270, value)
        elif line[0] == 'R':
            direction = rotate(direction, value)
        elif line[0] == 'L':
            direction = rotate(direction, -value)
    return abs(position[0]) + abs(position[1])


def rotate_waypoint(waypoint, degrees):
    if degrees < 0:
        degrees = degrees + 360
    degrees = degrees % 360
    if degrees == 0:
        return waypoint
    elif degrees == 90:
        return (waypoint[1], -waypoint[0])
    elif degrees == 180:
        return (-waypoint[0], -waypoint[1])
    elif degrees == 270:
        return (-waypoint[1], waypoint[0])


def part_two(lines):
    position = (0, 0)
    waypoint = (10, 1)
    for line in lines:
        value = int(line[1:])
        if line[0] == 'F':
            x_move = waypoint[0] * value
            y_move = waypoint[1] * value
            position = (position[0] + x_move, position[1] + y_move)
        elif line[0] == 'N':
            waypoint = (waypoint[0], waypoint[1] + value)
        elif line[0] == 'E':
            waypoint = (waypoint[0] + value, waypoint[1])
        elif line[0] == 'S':
            waypoint = (waypoint[0], waypoint[1] - value)
        elif line[0] == 'W':
            waypoint = (waypoint[0] - value, waypoint[1])
        elif line[0] == 'R':
            waypoint = rotate_waypoint(waypoint, value)
        elif line[0] == 'L':
            waypoint = rotate_waypoint(waypoint, -value)
    return abs(position[0]) + abs(position[1])


with open("input.txt", "r") as f:
    lines = f.read().splitlines()
    print(part_one(lines))
    print(part_two(lines))
