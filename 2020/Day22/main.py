from collections import deque
from copy import deepcopy


def parse_input(lines):
    player_one = deque()
    player_two = deque()
    for i, line in enumerate(lines[1:]):
        if line == '':
            break
        player_one.append(int(line))
    for line in lines[i+3:]:
        player_two.append(int(line))
    return player_one, player_two


def calculate_score(winner):
    result = 0
    for i, card in enumerate(winner):
        result += (len(winner) - i) * card
    return result


def part_one(player_one, player_two):
    while True:
        if player_one == deque():
            winner = player_two
            break
        elif player_two == deque():
            winner = player_one
            break
        p1_card = player_one.popleft()
        p2_card = player_two.popleft()
        if p1_card > p2_card:
            player_one.append(p1_card)
            player_one.append(p2_card)
        else:
            player_two.append(p2_card)
            player_two.append(p1_card)
    return calculate_score(winner)


def part_two(player_one, player_two, game=1):
    memory = []
    round = 0
    while True:
        if (player_one, player_two) in memory:
            winner = player_one
            winner_i = 1
            break
        memory.append((deepcopy(player_one), deepcopy(player_two)))
        if player_one == deque():
            winner = player_two
            winner_i = 2
            break
        elif player_two == deque():
            winner = player_one
            winner_i = 1
            break
        round += 1
        p1_card = player_one.popleft()
        p2_card = player_two.popleft()
        sub_i = 0
        if p1_card <= len(player_one) and p2_card <= len(player_two):
            sub_i, _ = part_two(deepcopy(deque(list(player_one)[:p1_card])),
                                deepcopy(deque(list(player_two)[:p2_card])),
                                game+1)
        if sub_i == 1 or (sub_i == 0 and p1_card > p2_card):
            player_one.append(p1_card)
            player_one.append(p2_card)
        else:
            player_two.append(p2_card)
            player_two.append(p1_card)
    if game == 1:
        return calculate_score(winner)
    return winner_i, winner


with open("input.txt", "r") as f:
    lines = f.read().splitlines()
    player_one, player_two = parse_input(lines)
    print(part_one(deepcopy(player_one), deepcopy(player_two)))
    print(part_two(player_one, player_two))
