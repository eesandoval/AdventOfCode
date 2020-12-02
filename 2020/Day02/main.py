from collections import namedtuple
password_policy = namedtuple("password_policy", "min max character password")

def parse_input(input_list):
    result = []
    for line in input_list:
        character_min = int(line.split('-')[0])
        character_max = int(line.split('-')[1].split(' ')[0])
        character = line.split(' ')[1].split(':')[0]
        password = line.split(':')[1].strip()
        result.append(password_policy(character_min, character_max, character, password))
    return result


def part_one(input_list):
    password_policies = parse_input(input_list)
    valid_passwords = 0
    for password_policy in password_policies:
        character_count = password_policy.password.count(password_policy.character)
        if character_count >= password_policy.min and character_count <= password_policy.max:
            valid_passwords = valid_passwords + 1
    return valid_passwords

def part_two(input_list):
    password_policies = parse_input(input_list)
    valid_passwords = 0
    for password_policy in password_policies:
        password = password_policy.password
        index1 = password_policy.min - 1
        index2 = password_policy.max - 1
        character = password_policy.character
        if index1 >= len(password) or index2 >= len(password):
            continue
        if bool(password[index1] == character) ^ bool(password[index2] == character):
            valid_passwords = valid_passwords + 1
    return valid_passwords
    

with open("input.txt", "r") as f:
    lines = f.read()
    lst = lines.split('\n')
    print(part_one(lst))
    print(part_two(lst))