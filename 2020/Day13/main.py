def part_one(lines):
    time = int(lines[0])
    min_diff = int(lines[0])
    bus_id = 0
    for line in lines[1].split(','):
        if line == 'x':
            continue
        current_id = int(line)
        diff = int(time / current_id) * current_id
        diff = diff + current_id - time
        if diff < min_diff:
            min_diff = diff
            bus_id = current_id
    return bus_id * min_diff


def part_two(lines):  # Use wolfram
    bus_ids = lines[1].split(',')
    return_str = "0 = "
    for i, n in enumerate(bus_ids):
        if n == 'x':
            continue
        return_str += "((n + " + str(i) + ") mod " + n + ") = "
    return return_str[:-2].strip()


with open("input.txt", "r") as f:
    lines = f.read().splitlines()
    print(part_one(lines))
    print(part_two(lines))
