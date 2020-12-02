def part_one(input_list):
    for first_number in input_list:
        second_number = 2020 - first_number
        if second_number in input_list:
            return second_number * first_number


def part_two(input_list):
    for first_number in input_list:
        for second_number in input_list:
            third_number = 2020 - first_number - second_number
            if third_number in input_list:
                return third_number * second_number * first_number


with open("input.txt", "r") as f:
    lines = f.read()
    lst = [int(x) for x in lines.split('\n')]
    print(part_one(lst))
    print(part_two(lst))
