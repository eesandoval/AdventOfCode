from math import log


def part_one(card_public, door_public):
    current = 1
    card_loop = 0
    while current != card_public:
        current *= 7
        current %= 20201227
        card_loop += 1
    card_loop = int(card_loop)
    result = 1
    for _ in range(card_loop):
        result *= door_public
        result %= 20201227
    return result


def part_two():
    return ":)"


with open("input.txt") as f:
    card_public, door_public = f.read().splitlines()
    card_public = int(card_public)
    door_public = int(door_public)
    print(part_one(card_public, door_public))
    print(part_two())
