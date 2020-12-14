import re
from itertools import chain, combinations


def parse_input(lines):
    result = {}
    values = []
    mask = ""
    for line in lines:
        if line.startswith("mask"):
            if len(values) > 0:
                result[mask] = values
                values = []
            mask = re.match(r"mask = ([X01]+)", line).groups()[0]
            continue
        value = re.match(r"mem\[([0-9]+)\] = ([0-9]+)", line).groups()
        values.append((int(value[0]), int(value[1])))
    result[mask] = values
    return result


def part_one(mask_values):
    memory = {}
    result = 0
    for mask, values in mask_values.items():
        for value in values:
            bitstring = format(value[1], '0' + str(len(mask)) + 'b')
            finalstring = list(mask)
            for i in range(len(bitstring)):
                if mask[i] == 'X':
                    finalstring[i] = bitstring[i]
                elif mask[i] == '0':
                    finalstring[i] = '0'
                elif mask[i] == '1':
                    finalstring[i] = '1'
            memory[value[0]] = "".join(finalstring)
    for value in memory.values():
        result += int(value, 2)
    return result


def part_two(mask_values):
    memory = {}
    result = 0
    for mask, values in mask_values.items():
        for value in values:
            bitstring = format(value[0], '0' + str(len(mask)) + 'b')
            finalstring = list(bitstring)
            twos = []
            for i in range(len(bitstring)):
                if mask[i] == 'X':
                    finalstring[i] = '0'
                    twos.append(2 ** (len(bitstring) - i - 1))
                elif mask[i] == '0':
                    finalstring[i] = bitstring[i]
                elif mask[i] == '1':
                    finalstring[i] = '1'
            address = int("".join(finalstring), 2)
            offsets = list(chain.from_iterable(combinations(twos, r)
                                               for r in range(len(twos) + 1)))
            for offset in offsets:
                memory[address + sum(offset)] = value[1]
    for value in memory.values():
        result += value
    return result


with open("input.txt", "r") as f:
    lines = f.read().splitlines()
    mask_values = parse_input(lines)
    print(part_one(mask_values))
    print(part_two(mask_values))
