import copy


def check_seats(lines, row, col, d_r, d_c, m_r, m_c, loop=False):
    if row >= m_r or row < 0 or col >= m_c or col < 0:
        return 0
    if row + d_r >= m_r or row + d_r < 0 or col + d_c >= m_c or col + d_c < 0:
        return 0
    if lines[row+d_r][col+d_c] == '#':
        return 1
    elif lines[row+d_r][col+d_c] == 'L':
        return 0
    if loop:
        return check_seats(lines, row+d_r, col+d_c, d_r, d_c, m_r, m_c, True)
    return 0


def conway_like_simulation(lines, loop=False, count_max=4):
    change = True
    m_r = len(lines)
    m_c = len(lines[0])
    n_lines = copy.deepcopy(lines)
    combinations = [(-1, 0), (0, -1), (-1, -1), (1, 0),
                    (0, 1), (1, 1), (1, -1), (-1, 1)]
    while change:
        change = False
        for row in range(0, m_r):
            for col in range(0, m_c):
                if lines[row][col] == '.':
                    continue
                count = 0
                for combo in combinations:
                    d_r = combo[0]
                    d_c = combo[1]
                    count += \
                        check_seats(lines, row, col, d_r, d_c, m_r, m_c, loop)
                if lines[row][col] == '#' and count >= count_max:
                    change = True
                    n_lines[row][col] = 'L'
                elif lines[row][col] == 'L' and count == 0:
                    change = True
                    n_lines[row][col] = '#'
        lines = copy.deepcopy(n_lines)
    result = 0
    for line in lines:
        for char in line:
            if char == '#':
                result += 1
    return result


with open("input.txt", "r") as f:
    lines = f.read().splitlines()
    matrix = []
    for line in lines:
        row = []
        for char in line:
            row.append(char)
        matrix.append(row)
    print(conway_like_simulation(matrix))
    print(conway_like_simulation(matrix, True, 5))
