def parenthetic_contents(string):
    ''' Thanks to Gareth Rees '''
    stack = []
    for i, c in enumerate(string):
        if c == '(':
            stack.append(i)
        elif c == ')' and stack:
            start = stack.pop()
            yield (len(stack), string[start + 1: i])


def new_math(line, override=False):
    ptr = 0
    sign = ''
    lhand = ""
    expr = ""
    lst = line.split()
    while ptr < len(lst):
        if lst[ptr] == '+' or lst[ptr] == '*':
            sign = lst[ptr]
            if override and lst[ptr] == '*':
                expr += lhand + " * "
                lhand = ""
        elif lhand == "":
            lhand = lst[ptr]
        else:
            lhand = str(eval(lhand + sign + lst[ptr]))
        ptr += 1
    if expr == "" or not(override):
        return int(lhand)
    return eval(expr + lhand)


def arithmetic(line, override_operator=False):
    memories = []
    parse_line = line
    pcs = list(parenthetic_contents(line))
    pcs.sort(reverse=True)
    for pc in pcs:
        expr = pc[1]
        for _, memory, answer in memories:
            expr = expr.replace(memory, answer)
        answer = str(new_math(expr, override_operator))
        str_repl = '(' + pc[1] + ')'
        memories.append((pc[0], str_repl, answer))
        memories.sort()
        if pc[0] == 0:
            parse_line = parse_line.replace(str_repl, answer)
    return new_math(parse_line, override_operator)


def part_one(lines):
    result = 0
    for line in lines:
        result += arithmetic(line)
    return result


def part_two(lines):
    result = 0
    for line in lines:
        result += arithmetic(line, True)
    return result


with open("input.txt", "r") as f:
    lines = f.read().splitlines()
    print(part_one(lines))
    print(part_two(lines))
