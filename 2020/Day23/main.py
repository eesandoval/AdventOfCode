from copy import deepcopy


def part_one(cups):
    min_cup, max_cup = min(cups), max(cups)
    move, cup_i = 0, 0
    while move < 100:
        cup = cups[cup_i]
        indexes = [(cup_i + i) % len(cups) for i in [1, 2, 3]]
        three_cups = [cups[i] for i in indexes]
        candidate, destination_cup = cup, False
        while not destination_cup:
            candidate -= 1
            if candidate < min_cup:
                candidate = max_cup
            if candidate not in three_cups:
                destination_cup = candidate
        if cups.index(cup) > cups.index(destination_cup):
            for sub_cup in three_cups:
                cups[cups.index(sub_cup)] = "X"
            for i, c in enumerate(three_cups, 1):
                cups.insert(cups.index(destination_cup) + i, c)
            for _ in range(3):
                cups.append(cups.pop(0))
            [cups.remove("X") for _ in range(3)]
        else:
            [cups.remove(c) for c in three_cups]
            for i, c in enumerate(three_cups, 1):
                cups.insert(cups.index(destination_cup) + i, c)
        cup_i = (cup_i + 1) % len(cups)
        move += 1
    labels, cup_1_index = "", cups.index(1)
    for _ in range(len(cups) - 1):
        cup_1_index += 1
        labels += str(cups[(cup_1_index) % len(cups)])
    return labels


def part_two(cups):
    cups = cups + [i for i in range(max(cups) + 1, 1000000 + 1)]
    min_cup, max_cup = min(cups), max(cups)
    cups_dict = {}
    for i, label in enumerate(cups, 1):
        cups_dict[label] = cups[i % 1000000]
    move, current_cup = 0, cups[0]
    while move < 10000000:
        three_cups = [cups_dict[current_cup],
                      cups_dict[cups_dict[current_cup]],
                      cups_dict[cups_dict[cups_dict[current_cup]]]]
        candidate, destination_cup = current_cup, False
        while not destination_cup:
            candidate -= 1
            if candidate < min_cup:
                candidate = max_cup
            if candidate not in three_cups:
                destination_cup = candidate
        cups_dict[current_cup] = cups_dict[three_cups[2]]
        cups_dict[three_cups[2]] = cups_dict[destination_cup]
        cups_dict[destination_cup] = three_cups[0]
        current_cup = cups_dict[current_cup]
        move += 1
    return cups_dict[1] * cups_dict[cups_dict[1]]


with open("input.txt") as f:
    cups = [int(cup) for cup in f.readline()]
    print(part_one(deepcopy(cups)))
    print(part_two(cups))
