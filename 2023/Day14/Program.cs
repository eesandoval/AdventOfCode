using System.Text;

int findRockNS(string[] matrix, int row, int col, int direction) // return row of the nearest rock
{
    for (var r = row; direction == -1 ? r >= 0 : r < matrix.Length; r += direction)
    {
        if (matrix[r][col] == '#')
            return r;
    }
    return -1;
}

int findRockEW(string[] matrix, int row, int col, int direction) // return row of the nearest rock
{
    for (var c = col; direction == -1 ? c >= 0 : c < matrix[0].Length; c += direction)
    {
        if (matrix[row][c] == '#')
            return c;
    }
    return -1;
}

string[] rollNS(string[] matrix, int direction)
{
    var newMatrix = new List<List<char>>();
    for (var r = 0; r < matrix.Length; r++)
    {
        var row = new List<char>();
        for (var c = 0; c < matrix[r].Length; c++)
        {
            if (matrix[r][c] == '#')
                row.Add('#');
            else
                row.Add('.');
        }
        newMatrix.Add(row);
    }

    for (var c = 0; c < matrix[0].Length; c++)
    {
        var minRock = -1;
        if (matrix[direction == 1 ? 0 : matrix.Length - 1][c] == '#')
            minRock = direction == 1 ? 0 : matrix.Length - 1;
        var maxRock = findRockNS(matrix, direction == 1 ? 0 : matrix.Length - 1, c, direction);
        while (maxRock != -1 && maxRock < matrix.Length)
        {
            for (var r = minRock + 1 * direction; r < maxRock; r++)
            {
                if (matrix[r][c] == 'O')
                {
                    newMatrix[++minRock][c] = 'O';
                }
            }
            minRock = maxRock;
            maxRock = findRockNS(matrix, maxRock + 1 * direction, c, direction);
            
        }
        for (var r = minRock + 1 * direction; direction == 1 ? r < matrix[0].Length : r >= 0; r += direction)
        {
            if (matrix[r][c] == 'O')
            {
                newMatrix[++minRock][c] = 'O';
            }
        }
    }
    return newMatrix.Select(x => string.Join("", x.ToArray())).ToArray();
}

string[] rollEW(string[] matrix, int direction)
{
    var newMatrix = new List<List<char>>();
    for (var r = 0; r < matrix.Length; r++)
    {
        var row = new List<char>();
        for (var c = 0; c < matrix[r].Length; c++)
        {
            if (matrix[r][c] == '#')
                row.Add('#');
            else
                row.Add('.');
        }
        newMatrix.Add(row);
    }

    for (var r = 0; r < matrix[0].Length; r++)
    {
        var minRock = -1;
        if (matrix[r][direction == 1 ? 0 : matrix[0].Length - 1] == '#')
            minRock = direction == 1 ? 0 : matrix[0].Length - 1;
        var maxRock = findRockEW(matrix, direction == 1 ? 0 : matrix[0].Length - 1, r, direction);
        while (maxRock != -1 && maxRock < matrix.Length)
        {
            for (var c = minRock + 1 * direction; c < maxRock; c++)
            {
                if (matrix[r][c] == 'O')
                {
                    newMatrix[++minRock][c] = 'O';
                }
            }
            minRock = maxRock;
            maxRock = findRockEW(matrix, maxRock + 1 * direction, r, direction);
            
        }
        for (var c = minRock + 1 * direction; direction == 1 ? c < matrix[0].Length : c >= 0; c += direction)
        {
            Console.WriteLine(c);
            if (matrix[r][c] == 'O')
            {
                newMatrix[++minRock][c] = 'O';
            }
        }
    }
    return newMatrix.Select(x => string.Join("", x.ToArray())).ToArray();
}

long calculateNorthLoad(string[] matrix)
{
    long result = 0;
    for (var r = 0; r < matrix.Length; r++)
    {
        for (var c = 0; c < matrix[r].Length; c++)
        {
            if (matrix[r][c] == 'O')
            {
                result += matrix.Length - r;
            }
        }
    }
    return result;
}

long partOne(string[] allLines)
{
    return calculateNorthLoad(rollNS(allLines, 1));
}

long partTwo(string[] allLines)
{
    var matrix = allLines;
    for (var i = 0; i < 1000000000; i++)
    {
        matrix = rollNS(matrix, 1);
        matrix = rollEW(matrix, -1);
        matrix = rollNS(matrix, -1);
        matrix = rollEW(matrix, 1);   
    }
    return calculateNorthLoad(matrix);
}

var allLines = File.ReadAllLines("input");
Console.WriteLine(partOne(allLines));
Console.WriteLine(partTwo(allLines));