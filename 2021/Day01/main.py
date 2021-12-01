def part_one(input_list):
    result = 0
    for i in range(1, len(input_list)):
        if input_list[i] > input_list[i - 1]:
            result += 1
    return result


def part_two(input_list):
    new_list = []
    for i in range(len(input_list) - 2):
        new_list.append(input_list[i] + input_list[i + 1] + input_list[i + 2])
    return part_one(new_list)


with open("input.txt", "r", encoding="utf-8") as f:
    lines = f.read()
    lst = [int(x) for x in lines.split('\n')]
    print(part_one(lst))
    print(part_two(lst))
