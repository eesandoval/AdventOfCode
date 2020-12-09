def part_one(lines, preamble=5):
    current_lst = lines[:preamble]
    current_index = preamble + 1
    while current_index < len(lines):
        i = lines[current_index]
        valid = False
        for k in current_lst:
            for j in current_lst:
                if k + j == i:
                    valid = True
                    break
            if valid:
                break
        if not(valid):
            return i
        current_index = current_index + 1
        current_lst = lines[current_index - preamble:current_index]


def part_two(lines, preamble):
    invalid = part_one(lines, preamble)
    pc = 0
    while True:
        current = 0
        values = set()
        for i in lines[pc:]:
            current = current + i
            values.add(i)
            if current == invalid:
                return min(values) + max(values)
            elif current > invalid:
                break
        pc = pc + 1


with open("input.txt", "r") as f:
    lines = [int(x) for x in f.read().splitlines()]
    print(part_one(lines, 25))
    print(part_two(lines, 25))
