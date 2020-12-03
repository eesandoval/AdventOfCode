def part_one(lines, r_increment=1, c_increment=3):
    row = 0
    col = 0
    trees = 0
    while True:
        row = row + r_increment
        if row >= len(lines):
            return trees
        col = (col + c_increment) % len(lines[row])
        if lines[row][col] == '#':
            trees = trees + 1


def part_two(lines):
    lst = [(1, 1), (1, 3), (1, 5), (1, 7), (2, 1)]
    result = 1
    for increments in lst:
        result = result * part_one(lines, increments[0], increments[1])
    return result


with open("input.txt", "r") as f:
    lines = f.read().split('\n')
    print(part_one(lines))
    print(part_two(lines))
