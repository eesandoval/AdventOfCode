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
    fields = ["byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"]
    for passport in passports:
        validated_fields = 0
        for field in fields:
            if field in passport.keys():
                validated_fields = validated_fields + 1
        if validated_fields == len(fields):
            valid.append(passport)
    return valid


def part_two(passports):
    initially_valid_passports = part_one(passports)
    valid = 0
    eye_colors = ["amb", "blu", "brn", "gry", "grn", "hzl", "oth"]
    for passport in initially_valid_passports:
        if not(1920 <= int(passport["byr"]) <= 2002):
            continue
        if not(2010 <= int(passport["iyr"]) <= 2020):
            continue
        if not(2020 <= int(passport["eyr"]) <= 2030):
            continue
        if "cm" not in passport["hgt"] and "in" not in passport["hgt"]:
            continue
        unit = passport["hgt"][-2:]
        height = int(passport["hgt"][:-2])
        if unit == "cm" and not(150 <= height <= 193):
            continue
        if unit == "in" and not(59 <= height <= 76):
            continue
        if passport["hcl"][0] != '#' or len(passport["hcl"][1:]) != 6:
            continue
        hcl_valid = True
        for c in passport["hcl"][1:]:
            if not(48 <= ord(c) <= 57) and not(97 <= ord(c) <= 122):
                hcl_valid = False
                break
        if not(hcl_valid):
            continue
        if passport["ecl"] not in eye_colors:
            continue
        if len(passport["pid"]) != 9 or not(passport["pid"].isdigit()):
            continue
        valid = valid + 1
    return valid


with open("input.txt", "r") as f:
    lines = f.read().splitlines()
    passports = parse_input(lines)
    print(len(part_one(passports)))
    print(part_two(passports))
