def part_one(lines):
    current_plug = 0
    differences = {1: 0, 2: 0, 3: 1}
    for line in lines:
        differences[line - current_plug] += 1
        current_plug = line
    return differences[1] * differences[3]


def combinations(data, index, cache):
    if index in cache:
        return cache[index]
    lst = []
    for i in range(index + 1, index + 4):
        if i in data:
            lst.append(combinations(data, i, cache))
    cache[index] = sum(lst)
    return cache[index]


def part_two(lines):
    cache = {lines[-1]: 1}
    combinations(lines, 0, cache)
    return cache[0]


with open("input.txt", "r") as f:
    lines = [int(x) for x in f.read().splitlines()]
    lines.sort()
    print(part_one(lines))
    print(part_two(lines))
