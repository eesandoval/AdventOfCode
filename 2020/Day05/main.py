def part_one(lines):
    ids = set()
    for line in lines:
        rows = range(0, 128)
        cols = range(0, 8)
        for c in line[:7]:
            if c == 'F':
                rows = rows[:len(rows)//2]
            else:
                rows = rows[len(rows)//2:]
        for c in line[7:]:
            if c == 'L':
                cols = cols[:len(cols)//2]
            else:
                cols = cols[len(cols)//2:]
        ids.add(rows[0] * 8 + cols[0])
    return ids


def part_two(lines):
    ids = part_one(lines)
    all_ids = set(range(min(ids), max(ids)))
    return all_ids.difference(ids)


with open("input.txt", "r") as f:
    lines = f.read().splitlines()
    print(max(part_one(lines)))
    print(part_two(lines))
