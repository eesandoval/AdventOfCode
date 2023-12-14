using System.Text;

List<string> rotateMatrixClockwise(List<string> matrix)
{
    List<string> result = new List<string>();
    for (var c = 0; c < matrix[0].Length; c++)
    {
        var stringBuilder = new StringBuilder();
        for (var r = matrix.Count - 1; r >= 0; r--)
        {
           // Console.WriteLine($"Row: {r}, col: {c}");
            stringBuilder.Append(matrix[r][c]);
        }
        result.Add(stringBuilder.ToString());
    }
    return result;
}

bool validateReflection(List<string> matrix, int r)
{
    var i = 0;
    while (r - i >= 0 && r + i + 1 < matrix.Count)
    {
        if (matrix[r - i] != matrix[r + i + 1])
        {
            return false;
        }
        i++;
    }
    return true;
}

int reflections(string[] allLines, bool p2 = false)
{
    var matrices = new List<List<string>>();
    var matrix = new List<string>();
    var verticals = new List<int>();
    var horizontals = new List<int>();
    foreach (var row in allLines)
    {
        if (string.IsNullOrEmpty(row))
        {
            matrices.Add(matrix);
            matrix = new List<string>();
        }
        else
        {
            matrix.Add(row);
        }
    }
    matrices.Add(matrix);

    // reflections across columns
    foreach (var m in matrices)
    {
        var mm = rotateMatrixClockwise(m);
        for (var r = 0; r < mm.Count - 1; r++)
        {
            if (mm[r] == mm[r+1] && ((!p2 && validateReflection(mm, r)) || (p2 && !validateReflection(mm, r))))
            {
                verticals.Add(r+1);
                continue;
            }
        }
    }

    // reflections across rows
    foreach (var m in matrices)
    {
        for (var r = 0; r < m.Count - 1; r++)
        {
            if (m[r] == m[r+1] && ((!p2 && validateReflection(m, r)) || (p2 && !validateReflection(m, r))))
            {
                horizontals.Add(r+1);
                continue;
            }
        }
    }
    return verticals.Sum() + 100 * horizontals.Sum();
}

int partOne(string[] allLines)
{
    return reflections(allLines);
}

int partTwo(string[] allLines)
{
    return reflections(allLines, true);
}

var allLines = File.ReadAllLines("input");
Console.WriteLine(partOne(allLines));
Console.WriteLine(partTwo(allLines));