import re


def parse_input(lines):
    rules = {}
    ticket = [int(x) for x in lines[1].split('\n')[1].split(',')]
    others = []
    for line in lines[0].split('\n'):
        m = re.match(r"([a-z\s]+):\s([0-9]+)-([0-9]+)\sor\s([0-9]+)-([0-9]+)",
                     line)
        lst = m.groups(0)
        dynamic_str = "({0}>=" + lst[1] + "and {0}<=" + lst[2] + ")"
        dynamic_str += "or ("
        dynamic_str += "{0} >=" + lst[3] + "and {0}<=" + lst[4] + ")"
        rules[lst[0]] = dynamic_str
    for line in lines[2].split('\n'):
        if line == "nearby tickets:":
            continue
        others.append([int(x) for x in line.split(',')])
    return (rules, ticket, others)


def part_one(rules, ticket, others):
    incorrect = []
    for other in others:
        for num in other:
            valid = False
            for rule in rules.values():
                if eval(rule.format(num)):
                    valid = True
                    break
            if not(valid):
                incorrect.append(num)
    return sum(incorrect)


def part_two(rules, ticket, others):
    invalid_tickets = []
    for other in others:
        for num in other:
            valid = False
            for rule in rules.values():
                if eval(rule.format(num)):
                    valid = True
                    break
            if not(valid):
                invalid_tickets.append(other)
                break
    possibilities = {}
    for other in others:
        if other in invalid_tickets:
            continue
        possible = {}
        for i, num in enumerate(other):
            for desc, rule in rules.items():
                if eval(rule.format(num)):
                    if desc not in possible:
                        possible[desc] = set()
                    possible[desc] = possible[desc].union({i})
        for desc, p in possible.items():
            if desc not in possibilities:
                possibilities[desc] = p
            elif len(possibilities[desc]) == 1:
                continue
            else:
                possibilities[desc] = possibilities[desc].intersection(p)
    unique = False
    while not(unique):
        unique = True
        for desc, p in possibilities.items():
            if len(possibilities[desc]) == 1:
                remove = next(iter(possibilities[desc]))
                for dd in possibilities:
                    if dd != desc:
                        possibilities[dd].discard(remove)
            else:
                unique = False
    result = 1
    for desc, s in possibilities.items():
        index = next(iter(s))
        value = ticket[index]
        if desc.startswith("departure"):
            result *= value
    return result


with open("input.txt", "r") as f:
    lines = f.read().split("\n\n")
    info = parse_input(lines)
    print(part_one(info[0], info[1], info[2]))
    print(part_two(info[0], info[1], info[2]))
