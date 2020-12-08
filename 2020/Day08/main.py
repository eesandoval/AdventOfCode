import re
import copy


def parse_input(lines):
    result = []
    for line in lines:
        matches = re.search(r"([a-z]{3})\s([\+-])(\d+)", line)
        operation = (matches.group(1), matches.group(2), matches.group(3))
        result.append(operation)
    return result


def part_one(operations):
    accumulator = 0
    pc = 0
    clean_exit = True
    seen_operations = set()
    while pc < len(operations):
        opcode = operations[pc][0]
        argument = int(operations[pc][1] + operations[pc][2])
        if opcode == "nop":
            pc = pc + 1
        elif opcode == "acc":
            accumulator = accumulator + argument
            pc = pc + 1
        elif opcode == "jmp":
            pc = pc + argument
        if pc in seen_operations:
            clean_exit = False
            break
        seen_operations.add(pc)
    return (accumulator, clean_exit)


def part_two(operations):
    original_operations = copy.deepcopy(operations)
    for i in range(0, len(original_operations)):
        opcode = operations[i][0]
        argument_sign = operations[i][1]
        argument = operations[i][2]
        if opcode == "acc":
            continue
        elif opcode == "nop":
            operations[i] = ("jmp", argument_sign, argument)
        elif opcode == "jmp":
            operations[i] = ("nop", argument_sign, argument)
        if part_one(operations)[1]:
            return part_one(operations)[0]
        operations = copy.deepcopy(original_operations)


with open("input.txt", "r") as f:
    lines = f.read().splitlines()
    operations = parse_input(lines)
    print(part_one(operations)[0])
    print(part_two(operations))
