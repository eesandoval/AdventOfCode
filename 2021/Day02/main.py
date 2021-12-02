def part_one(input_list):
    horizontal = 0
    depth = 0
    for command in input_list:
        direction = command[0]
        unit = command[1]
        if direction == 'forward':
            horizontal += unit
        elif direction == 'down':
            depth += unit
        else:
            depth -= unit
    return horizontal * depth


def part_two(input_list):
    horizontal = 0
    depth = 0
    aim = 0
    for command in input_list:
        direction = command[0]
        unit = command[1]
        if direction == 'forward':
            horizontal += unit
            depth += aim * unit
        elif direction == 'down':
            aim += unit
        else:
            aim -= unit
    return horizontal * depth


with open("input.txt", "r", encoding="utf-8") as f:
    lines = f.read()
    lst = [(x.split(' ')[0], int(x.split(' ')[1])) for x in lines.split('\n')]
    print(part_one(lst))
    print(part_two(lst))
