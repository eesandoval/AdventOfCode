def part_one(input_list):
    gamma_rate_lst = []
    for col in range(len(input_list[0])):
        num_ones = 0
        num_zeros = 0
        for row in input_list:
            if row[col] == '1':
                num_ones += 1
            else:
                num_zeros += 1
        if num_ones > num_zeros:
            gamma_rate_lst.append(1)
        else:
            gamma_rate_lst.append(0)
    gamma_rate = int("".join(str(i) for i in gamma_rate_lst), 2)
    epsilon_rate = int("".join(str((i + 1) % 2) for i in gamma_rate_lst), 2)
    return gamma_rate * epsilon_rate


def part_two(input_list):
    oxygen_list = input_list
    co2_list = input_list
    for col in range(len(input_list[0])):
        if len(oxygen_list) > 1:
            num_ones = 0
            num_zeros = 0
            most_common = '1'
            new_oxygen_list = []
            new_co2_list = []
            for row in oxygen_list:
                if row[col] == '1':
                    num_ones += 1
                else:
                    num_zeros += 1
            if num_zeros > num_ones:
                most_common = '0'
            for row in oxygen_list:
                if row[col] == most_common:
                    new_oxygen_list.append(row)
            oxygen_list = new_oxygen_list

        if len(co2_list) == 1:
            continue
        num_ones = 0
        num_zeros = 0
        least_common = '0'
        for row in co2_list:
            if row[col] == '1':
                num_ones += 1
            else:
                num_zeros += 1
        if num_ones < num_zeros:
            least_common = '1'
        for row in co2_list:
            if row[col] == least_common:
                new_co2_list.append(row)
        co2_list = new_co2_list
    oxygen_rating = int("".join(str(i) for i in oxygen_list), 2)
    co2_rating = int("".join(str(i) for i in co2_list), 2)
    return oxygen_rating * co2_rating


with open("input.txt", "r", encoding="utf-8") as f:
    lines = f.read()
    lst = [x for x in lines.split('\n')]
    print(part_one(lst))
    print(part_two(lst))
