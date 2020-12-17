import copy


def print_space(space, suppress=False):
    offset = len(space) // 2
    big_string = ""
    for i, z in enumerate(space):
        string = ""
        for x in z:
            for y in x:
                string += y
            string += '\n'
        if '#' not in string:
            continue
        if not(suppress):
            print("z=" + str(i - offset))
            print(string)
        big_string += "z=" + str(i - offset) + '\n' + string + '\n'
    return big_string


def print_dimension(dimension):
    offset = len(dimension) // 2
    for i, t in enumerate(dimension):
        big_string = print_space(t, True)
        if '#' not in big_string:
            continue
        print("t=" + str(i - offset))
        print(big_string)


def check_space(space, aisle, row, col, d_a, d_r, d_c, m_a, m_r, m_c):
    if aisle >= m_a or row >= m_r or aisle < 0 or row < 0 or col >= m_c or \
       col < 0:
        return 0
    if aisle + d_a >= m_a or aisle + d_a < 0 or row + d_r >= m_r or \
       row + d_r < 0 or col + d_c >= m_c or col + d_c < 0:
        return 0
    if space[aisle+d_a][row+d_r][col+d_c] == '#':
        return 1
    elif space[aisle+d_a][row+d_r][col+d_c] == '.':
        return 0
    return 0


def check_d(dimension, time, aisle, row, col, d_t, d_a, d_r, d_c, m_t, m_a,
            m_r, m_c):
    if time >= m_t or time < 0 or aisle >= m_a or row >= m_r or aisle < 0 or \
       row < 0 or col >= m_c or col < 0:
        return 0
    if time + d_t >= m_t or time + d_t < 0 or aisle + d_a >= m_a or \
       aisle + d_a < 0 or row + d_r >= m_r or row + d_r < 0 or \
       col + d_c >= m_c or col + d_c < 0:
        return 0
    if dimension[time+d_t][aisle+d_a][row+d_r][col+d_c] == '#':
        return 1
    elif dimension[time+d_t][aisle+d_a][row+d_r][col+d_c] == '.':
        return 0
    return 0


def part_one(matrix):
    m_c = len(matrix[0]) + 12
    m_r = len(matrix) + 12
    m_a = 13
    space = []
    for _ in range(6):
        aisle = []
        for _ in range(m_r):
            row = []
            for _ in range(m_c):
                row.append('.')
            aisle.append(row)
        space.append(aisle)
    sub_aisle = []
    for _ in range((m_r - len(matrix)) // 2):
        row = []
        for _ in range(m_c):
            row.append('.')
        sub_aisle.append(row)
    for row in matrix:
        new_row = []
        for _ in range((m_c - len(matrix[0])) // 2):
            new_row.append('.')
        for col in row:
            new_row.append(col)
        for _ in range((m_c - len(matrix[0])) // 2):
            new_row.append('.')
        sub_aisle.append(new_row)
    for _ in range((m_r - len(matrix)) // 2):
        row = []
        for _ in range(m_c):
            row.append('.')
        sub_aisle.append(row)
    space.append(sub_aisle)
    for _ in range(6):
        aisle = []
        for _ in range(m_r):
            row = []
            for _ in range(m_c):
                row.append('.')
            aisle.append(row)
        space.append(aisle)
    new_space = copy.deepcopy(space)
    combinations = [(-1, -1, -1), (-1, -1, 0), (-1, -1, 1), (-1, 0, -1),
                    (-1, 0, 0), (-1, 0, 1), (-1, 1, -1), (-1, 1, 0),
                    (-1, 1, 1), (0, -1, -1), (0, -1, 0), (0, -1, 1),
                    (0, 0, -1), (0, 0, 1), (0, 1, -1), (0, 1, 0),
                    (0, 1, 1), (1, -1, -1), (1, -1, 0), (1, -1, 1),
                    (1, 0, -1), (1, 0, 0), (1, 0, 1), (1, 1, -1),
                    (1, 1, 0), (1, 1, 1)]
    for _ in range(6):
        for aisle, z in enumerate(space):
            for row, x in enumerate(z):
                for col, y in enumerate(x):
                    count = 0
                    for combo in combinations:
                        d_a = combo[0]
                        d_r = combo[1]
                        d_c = combo[2]
                        count += \
                            check_space(space, aisle, row, col, d_a, d_r, d_c,
                                        m_a, m_r, m_c)
                    if y == '#' and (count < 2 or count > 3):
                        new_space[aisle][row][col] = '.'
                    elif y == '.' and count == 3:
                        new_space[aisle][row][col] = '#'
        space = copy.deepcopy(new_space)
    result = 0
    for z in space:
        for x in z:
            for y in x:
                if y == '#':
                    result += 1
    print_space(space)
    return result


def part_two(matrix):
    m_c = len(matrix[0]) + 12
    m_r = len(matrix) + 12
    m_a = 13
    m_t = 13
    dimension = []
    for _ in range(m_t // 2):
        space = []
        for _ in range(m_a):
            aisle = []
            for _ in range(m_r):
                row = []
                for _ in range(m_c):
                    row.append('.')
                aisle.append(row)
            space.append(aisle)
        dimension.append(space)
    sub_aisle = []
    sub_space = []
    for _ in range(6):
        aisle = []
        for _ in range(m_r):
            row = []
            for _ in range(m_c):
                row.append('.')
            aisle.append(row)
        sub_space.append(aisle)
    for _ in range((m_r - len(matrix)) // 2):
        row = []
        for _ in range(m_c):
            row.append('.')
        sub_aisle.append(row)
    for row in matrix:
        new_row = []
        for _ in range((m_c - len(matrix[0])) // 2):
            new_row.append('.')
        for col in row:
            new_row.append(col)
        for _ in range((m_c - len(matrix[0])) // 2):
            new_row.append('.')
        sub_aisle.append(new_row)
    for _ in range((m_r - len(matrix)) // 2):
        row = []
        for _ in range(m_c):
            row.append('.')
        sub_aisle.append(row)
    sub_space.append(sub_aisle)
    for _ in range(6):
        aisle = []
        for _ in range(m_r):
            row = []
            for _ in range(m_c):
                row.append('.')
            aisle.append(row)
        sub_space.append(aisle)
    dimension.append(sub_space)
    for _ in range(m_t // 2):
        space = []
        for _ in range(m_a):
            aisle = []
            for _ in range(m_r):
                row = []
                for _ in range(m_c):
                    row.append('.')
                aisle.append(row)
            space.append(aisle)
        dimension.append(space)
    new_d = copy.deepcopy(dimension)
    combinations = [(-1, -1, -1, -1), (-1, -1, -1, 0), (-1, -1, -1, 1),
                    (-1, -1, 0, -1), (-1, -1, 0, 0), (-1, -1, 0, 1),
                    (-1, -1, 1, -1), (-1, -1, 1, 0), (-1, -1, 1, 1),
                    (-1, 0, -1, -1), (-1, 0, -1, 0), (-1, 0, -1, 1),
                    (-1, 0, 0, -1), (-1, 0, 0, 1), (-1, 0, 1, -1),
                    (-1, 0, 1, 0), (-1, 0, 1, 1), (-1, 1, -1, -1),
                    (-1, 1, -1, 0), (-1, 1, -1, 1), (-1, 1, 0, -1),
                    (-1, 1, 0, 0), (-1, 1, 0, 1), (-1, 1, 1, -1),
                    (-1, 1, 1, 0), (-1, 1, 1, 1), (0, -1, -1, -1),
                    (0, -1, -1, 0), (0, -1, -1, 1), (0, -1, 0, -1),
                    (0, -1, 0, 0), (0, -1, 0, 1), (0, -1, 1, -1),
                    (0, -1, 1, 0), (0, -1, 1, 1), (0, 0, -1, -1),
                    (0, 0, -1, 0), (0, 0, -1, 1), (0, 0, 0, -1),
                    (0, 0, 0, 1), (0, 0, 1, -1), (0, 0, 1, 0),
                    (0, 0, 1, 1), (0, 1, -1, -1), (0, 1, -1, 0),
                    (0, 1, -1, 1), (0, 1, 0, -1), (0, 1, 0, 0),
                    (0, 1, 0, 1), (0, 1, 1, -1), (0, 1, 1, 0),
                    (0, 1, 1, 1), (1, -1, -1, -1), (1, -1, -1, 0),
                    (1, -1, -1, 1), (1, -1, 0, -1), (1, -1, 0, 0),
                    (1, -1, 0, 1), (1, -1, 1, -1), (1, -1, 1, 0),
                    (1, -1, 1, 1), (1, 0, -1, -1), (1, 0, -1, 0),
                    (1, 0, -1, 1), (1, 0, 0, -1), (1, 0, 0, 1),
                    (1, 0, 1, -1), (1, 0, 1, 0), (1, 0, 1, 1),
                    (1, 1, -1, -1), (1, 1, -1, 0), (1, 1, -1, 1),
                    (1, 1, 0, -1), (1, 1, 0, 0), (1, 1, 0, 1),
                    (1, 1, 1, -1), (1, 1, 1, 0), (1, 1, 1, 1),
                    (-1, 0, 0, 0), (1, 0, 0, 0)]
    for _ in range(6):
        for time, t in enumerate(dimension):
            for aisle, z in enumerate(t):
                for row, x in enumerate(z):
                    for col, y in enumerate(x):
                        count = 0
                        for combo in combinations:
                            d_t = combo[0]
                            d_a = combo[1]
                            d_r = combo[2]
                            d_c = combo[3]
                            count += \
                                check_d(dimension, time, aisle, row, col, d_t,
                                        d_a, d_r, d_c, m_t, m_a, m_r, m_c)
                        if y == '#' and (count < 2 or count > 3):
                            new_d[time][aisle][row][col] = '.'
                        elif y == '.' and count == 3:
                            new_d[time][aisle][row][col] = '#'
        dimension = copy.deepcopy(new_d)
    result = 0
    for t in dimension:
        for z in t:
            for x in z:
                for y in x:
                    if y == '#':
                        result += 1
    return result


with open("input.txt", "r") as f:
    lines = f.read().splitlines()
    matrix = []
    for line in lines:
        matrix.append(list(line))
    print(part_two(matrix))
