import re


def generate_rule(s, depth, ruledict):
    if (depth > max_length):
        return ""
    depth += 1
    if (not any(char.isdigit() for char in s)):
        return s.replace('"', '')

    elif("|" in s):
        rules1, rules2 = s.split(" | ")
        return '(' + generate_rule(rules1, depth, ruledict) + "|" + \
            generate_rule(rules2, depth, ruledict) + ")"

    elif(" " in s):
        split = s.split(" ")
        rule = ""
        for r in split:
            rule += generate_rule(r, depth, ruledict)
        return rule

    else:
        return generate_rule(ruledict[s], depth, ruledict)


def parse_input(filename):
    l_string = open(filename).read().rstrip()
    l_string = l_string.replace("\n\n", "\t").replace("\n", "^").split("\t")
    l_string = [sub.split("^") for sub in l_string]
    return l_string


def day19(l_string, l_rules):
    rule_dict = generate_dictionary(l_rules)
    regex = re.compile(generate_rule('0', 0, rule_dict))
    count = 0
    for string in l_string:
        if (regex.fullmatch(string)):
            count += 1
    return count


def generate_dictionary(l_rules):
    dictionary = {}
    for rule in l_rules:
        split = rule.split(": ")
        dictionary[split[0]] = split[1]
    return dictionary


def part_one():
    global max_length
    l_rules, l_string = parse_input("input.txt")
    max_length = len(max(l_string, key=len))
    print(day19(l_string, l_rules))


def part_two():
    global max_length
    l_rules, l_string = parse_input("input2.txt")
    max_length = len(max(l_string, key=len))
    print(day19(l_string, l_rules))


max_length = 0
part_one()
part_two()
