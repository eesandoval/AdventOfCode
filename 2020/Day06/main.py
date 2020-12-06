def part_one(lines):
    result = 0
    answers = set()
    for line in lines:
        if line == '':
            result = result + len(answers)
            answers = set()
            continue
        answers = answers.union(set(list(line)))
    return result + len(answers)


def part_two(lines):
    result = 0
    answers = set()
    first = True
    for line in lines:
        if line == '':
            result = result + len(answers)
            answers = set()
            first = True
            continue
        if first:
            answers = set(list(line))
            first = False
        else:
            answers = answers.intersection(set(list(line)))
    return result + len(answers)


with open("input.txt", "r") as f:
    lines = f.read().splitlines()
    print(part_one(lines))
    print(part_two(lines))
