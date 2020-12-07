def parse_rules(lines):
    bag_rules = {}
    for line in lines:
        bag = line.split("bags")[0].strip()
        contains = {}
        for b in line.split("contain")[1].replace('.', '').strip().split(','):
            if b == "no other bags":
                break
            num = int(b.strip().split(' ')[0])
            sub_bag = ' '.join(b.strip().split(' ')[1:-1])
            contains[sub_bag] = num
        bag_rules[bag] = contains
    return bag_rules


def part_one(bag_rules, bag_to_find):
    result = set()
    for bag, rule in bag_rules.items():
        if bag == bag_to_find:
            continue
        if bag_to_find in rule.keys():
            result.add(bag)
            result = result.union(part_one(bag_rules, bag))
    return result


def part_two(bag_rules, bag_to_find):
    rules = bag_rules[bag_to_find]
    result = 1
    for bag, count in rules.items():
        result = result + count * part_two(bag_rules, bag)
    return result


with open("input.txt", "r") as f:
    lines = f.read().splitlines()
    bag_rules = parse_rules(lines)
    print(len(part_one(bag_rules, "shiny gold")))
    print(part_two(bag_rules, "shiny gold") - 1)  # Uncount the shiny bag
