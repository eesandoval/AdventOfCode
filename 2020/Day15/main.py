def part_one(numbers, turn_length=2020):
    memory = {}
    turn = len(numbers) + 1
    last_spoken = 0
    new_number = True
    for n, number in enumerate(numbers):
        memory[int(number)] = [n + 1]
        last_spoken = int(number)
    while turn <= turn_length:
        if new_number:
            last_spoken = 0
        else:
            last_spoken = abs(memory[last_spoken][0] - memory[last_spoken][1])
        if last_spoken in memory.keys():
            if len(memory[last_spoken]) < 2:
                memory[last_spoken].append(turn)
            else:
                i = min(memory[last_spoken])
                memory[last_spoken][memory[last_spoken].index(i)] = turn
            new_number = False
        else:
            new_number = True
            memory[last_spoken] = [turn]
        turn += 1
    return last_spoken


def part_two(numbers):
    return part_one(numbers, 30000000)


with open("input.txt", "r") as f:
    numbers = f.read().split(',')
    print(part_one(numbers))
    print(part_two(numbers))
