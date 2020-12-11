import copy


def part_one(lines):
    change = True
    m_r = len(lines)
    m_c = len(lines[0])
    c_lines = copy.deepcopy(lines)
    n_lines = copy.deepcopy(lines)
    while change:
        change = False
        for row in range(0, m_r):
            for col in range(0, m_c):
                if lines[row][col] == '.':
                    continue
                neighbors = 0
                if row - 1 >= 0 and c_lines[row-1][col] == '#':
                    neighbors += 1
                if col - 1 >= 0 and c_lines[row][col-1] == '#':
                    neighbors += 1
                if row - 1 >= 0 and col - 1 >= 0 and \
                        c_lines[row-1][col-1] == '#':
                    neighbors += 1
                if row + 1 < m_r and c_lines[row+1][col] == '#':
                    neighbors += 1
                if col + 1 < m_c and c_lines[row][col+1] == '#':
                    neighbors += 1
                if row + 1 < m_r and col + 1 < m_c and \
                        c_lines[row+1][col+1] == '#':
                    neighbors += 1
                if row + 1 < m_r and col - 1 >= 0 and \
                        c_lines[row+1][col-1] == '#':
                    neighbors += 1
                if row - 1 >= 0 and col + 1 < m_c and \
                        c_lines[row-1][col+1] == '#':
                    neighbors += 1
                if c_lines[row][col] == '#' and neighbors >= 4:
                    change = True
                    n_lines[row][col] = 'L'
                elif c_lines[row][col] == 'L' and neighbors == 0:
                    change = True
                    n_lines[row][col] = '#'
        c_lines = copy.deepcopy(n_lines)
    result = 0
    for line in c_lines:
        for char in line:
            if char == '#':
                result += 1
    return result


def check_direction(matrix, row, col, d_r, d_c, m_r, m_c):
    if row >= m_r or row < 0 or col >= m_c or col < 0:
        return 0
    if row + d_r >= m_r or row + d_r < 0 or col + d_c >= m_c or col + d_c < 0:
        return 0
    if matrix[row+d_r][col+d_c] == '#':
        return 1
    elif matrix[row+d_r][col+d_c] == 'L':
        return 0
    return check_direction(matrix, row+d_r, col+d_c, d_r, d_c, m_r, m_c)


def part_two(lines):
    change = True
    m_r = len(lines)
    m_c = len(lines[0])
    c_lines = copy.deepcopy(lines)
    n_lines = copy.deepcopy(lines)
    while change:
        change = False
        for row in range(0, m_r):
            for col in range(0, m_c):
                if lines[row][col] == '.':
                    continue
                count = 0
                count += check_direction(c_lines, row, col, -1, 0, m_r, m_c)
                count += check_direction(c_lines, row, col, 0, -1, m_r, m_c)
                count += check_direction(c_lines, row, col, -1, -1, m_r, m_c)
                count += check_direction(c_lines, row, col, 1, 0, m_r, m_c)
                count += check_direction(c_lines, row, col, 0, 1, m_r, m_c)
                count += check_direction(c_lines, row, col, 1, 1, m_r, m_c)
                count += check_direction(c_lines, row, col, -1, 1, m_r, m_c)
                count += check_direction(c_lines, row, col, 1, -1, m_r, m_c)
                if c_lines[row][col] == '#' and count >= 5:
                    change = True
                    n_lines[row][col] = 'L'
                elif c_lines[row][col] == 'L' and count == 0:
                    change = True
                    n_lines[row][col] = '#'
        c_lines = copy.deepcopy(n_lines)
    result = 0
    for line in c_lines:
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
    print(part_one(matrix))
    print(part_two(matrix))
