from re import match


def parse_input(lines):
    passports = [{}]
    passport = {}
    for line in lines:
        if line == '':
            passports.append(passport)
            passport = {}
        else:
            for field in line.split(' '):
                passport[field.split(':')[0]] = field.split(':')[1]
    passports.append(passport)
    return passports


def part_one(passports):
    valid = []
    fields = {"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"}
    for passport in passports:
        if fields.intersection(set(passport.keys())) == fields:
            valid.append(passport)
    return valid


def part_two(passports):
    initially_valid_passports = part_one(passports)
    valid = 0
    eye_colors = ["amb", "blu", "brn", "gry", "grn", "hzl", "oth"]
    for psp in initially_valid_passports:
        if not(1920 <= int(psp["byr"]) <= 2002):
            continue
        if not(2010 <= int(psp["iyr"]) <= 2020):
            continue
        if not(2020 <= int(psp["eyr"]) <= 2030):
            continue
        if "cm" not in psp["hgt"] and "in" not in psp["hgt"]:
            continue
        if psp["hgt"][-2:] == "cm" and not(150 <= int(psp["hgt"][:-2]) <= 193):
            continue
        if psp["hgt"][-2:] == "in" and not(59 <= int(psp["hgt"][:-2]) <= 76):
            continue
        if match("^#[0-9a-f]{6}$", psp["hcl"]) is None:
            continue
        if psp["ecl"] not in eye_colors:
            continue
        if len(psp["pid"]) != 9 or not(psp["pid"].isdigit()):
            continue
        valid = valid + 1
    return valid


with open("input.txt", "r") as f:
    lines = f.read().splitlines()
    passports = parse_input(lines)
    print(len(part_one(passports)))
    print(part_two(passports))
