from re import compile, match
from collections import namedtuple

pass_policy = namedtuple("pass_policy", "min max character password")


def parse_input(input_list):
    result = []
    pattern = compile(r"([0-9]+)-([0-9]+)\s([a-z]):\s([a-z]+)")
    for line in input_list:
        m = pattern.match(line)
        policy = pass_policy(int(m.group(1)), int(m.group(2)),
                             m.group(3), m.group(4))
        result.append(policy)
    return result


def part_one(input_list):
    valid_passwords = 0
    for policy in input_list:
        count = policy.password.count(policy.character)
        if count >= policy.min and count <= policy.max:
            valid_passwords = valid_passwords + 1
    return valid_passwords


def part_two(input_list):
    valid_passwords = 0
    for policy in input_list:
        index1 = policy.min - 1
        index2 = policy.max - 1
        password = policy.password
        character = policy.character
        if (password[index1] == character) ^ (password[index2] == character):
            valid_passwords = valid_passwords + 1
    return valid_passwords


with open("input.txt", "r") as f:
    lines = f.read()
    lst = parse_input(lines.split('\n'))
    print(part_one(lst))
    print(part_two(lst))
