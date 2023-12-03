using System.Text;
using System.Text.RegularExpressions;

var symbols = new Regex(@"([^\d\.])", RegexOptions.Compiled);
var numbers = new Regex(@"(\d+)", RegexOptions.Compiled);

(int, int, int) GetFullNumber(string[] allLines, int row, int col)
{
    var sb = new StringBuilder();
    var currentC = allLines[row][col];
    int sCol = col, eCol = col + 1;
    while (int.TryParse(currentC.ToString(), out _)) // look left
    {
        sb.Insert(0, currentC.ToString());
        if (--sCol < 0)
            break;
        currentC = allLines[row][sCol];
    }
    if (eCol >= allLines[0].Length)
    {
        int.TryParse(sb.ToString(), out int r);
        return (row, sCol + 1, r);
    }
    currentC = allLines[row][eCol];
    while (int.TryParse(currentC.ToString(), out _)) // look right
    {
        sb.Append(currentC.ToString());
        if (++eCol >= allLines[0].Length)
            break;
        currentC = allLines[row][eCol];
    }
    int.TryParse(sb.ToString(), out int result);
    return (row, sCol + 1, result);
}

int partOne(string[] allLines)
{
    var result = 0;
    var numberLocations = new HashSet<(int, int, int)>(); // x, y, number
    for (var i = 0; i < allLines.Length; i++)
    {
        var matches = symbols.Matches(allLines[i]);
        foreach (Match m in matches)
        {
            int r = i, c = m.Groups[0].Index;
            if (r - 1 >= 0 && c - 1 >= 0 && int.TryParse(allLines[r - 1][c - 1].ToString(), out _)) // r - 1, c - 1
            {
                numberLocations.Add(GetFullNumber(allLines, r - 1, c - 1));
            }
            if (r - 1 >= 0 && int.TryParse(allLines[r - 1][c].ToString(), out _)) // r - 1, c
            {
                numberLocations.Add(GetFullNumber(allLines, r - 1, c));
            }
            if (r - 1 >= 0 && c + 1 < allLines[0].Length && int.TryParse(allLines[r - 1][c + 1].ToString(), out _)) // r - 1, c + 1
            {
                numberLocations.Add(GetFullNumber(allLines, r - 1, c + 1));
            }
            if (c - 1 >= 0 && int.TryParse(allLines[r][c - 1].ToString(), out _)) // r, c - 1
            {
                numberLocations.Add(GetFullNumber(allLines, r, c - 1));
            }
            if (c + 1 < allLines[0].Length && int.TryParse(allLines[r][c + 1].ToString(), out _)) // r, c + 1
            {
                numberLocations.Add(GetFullNumber(allLines, r, c + 1));
            }
            if (r + 1 < allLines.Length && c - 1 >= 0 && int.TryParse(allLines[r + 1][c - 1].ToString(), out _)) // r + 1, c - 1
            {
                numberLocations.Add(GetFullNumber(allLines, r + 1, c - 1));
            }
            if (r + 1 < allLines.Length && int.TryParse(allLines[r + 1][c].ToString(), out _)) // r + 1, c
            {
                numberLocations.Add(GetFullNumber(allLines, r + 1, c));
            }
            if (r + 1 < allLines.Length && c + 1 < allLines[0].Length && int.TryParse(allLines[r + 1][c + 1].ToString(), out _)) // r + 1, c + 1
            {
                numberLocations.Add(GetFullNumber(allLines, r + 1, c + 1));
            }
        }
    }
    
    foreach (var numberLocation in numberLocations)
    {
        result += numberLocation.Item3;
    }
    return result;
}

int partTwo(string[] allLines)
{
    var result = 0;
    var allNumbers = new List<int>();
    for (var i = 0; i < allLines.Length; i++)
    {
        var matches = symbols.Matches(allLines[i]);
        foreach (Match m in matches)
        {
            if (m.Groups[0].Value != "*")
                continue;
            var numberLocations = new HashSet<(int, int, int)>(); // x, y, number
            int r = i, c = m.Groups[0].Index;
            if (r - 1 >= 0 && c - 1 >= 0 && int.TryParse(allLines[r - 1][c - 1].ToString(), out _)) // r - 1, c - 1
            {
                numberLocations.Add(GetFullNumber(allLines, r - 1, c - 1));
            }
            if (r - 1 >= 0 && int.TryParse(allLines[r - 1][c].ToString(), out _)) // r - 1, c
            {
                numberLocations.Add(GetFullNumber(allLines, r - 1, c));
            }
            if (r - 1 >= 0 && c + 1 < allLines[0].Length && int.TryParse(allLines[r - 1][c + 1].ToString(), out _)) // r - 1, c + 1
            {
                numberLocations.Add(GetFullNumber(allLines, r - 1, c + 1));
            }
            if (c - 1 >= 0 && int.TryParse(allLines[r][c - 1].ToString(), out _)) // r, c - 1
            {
                numberLocations.Add(GetFullNumber(allLines, r, c - 1));
            }
            if (c + 1 < allLines[0].Length && int.TryParse(allLines[r][c + 1].ToString(), out _)) // r, c + 1
            {
                numberLocations.Add(GetFullNumber(allLines, r, c + 1));
            }
            if (r + 1 < allLines.Length && c - 1 >= 0 && int.TryParse(allLines[r + 1][c - 1].ToString(), out _)) // r + 1, c - 1
            {
                numberLocations.Add(GetFullNumber(allLines, r + 1, c - 1));
            }
            if (r + 1 < allLines.Length && int.TryParse(allLines[r + 1][c].ToString(), out _)) // r + 1, c
            {
                numberLocations.Add(GetFullNumber(allLines, r + 1, c));
            }
            if (r + 1 < allLines.Length && c + 1 < allLines[0].Length && int.TryParse(allLines[r + 1][c + 1].ToString(), out _)) // r + 1, c + 1
            {
                numberLocations.Add(GetFullNumber(allLines, r + 1, c + 1));
            }
            if (numberLocations.Count == 2)
            {
                var numbers = numberLocations.ToList();
                result += numbers[0].Item3 * numbers[1].Item3;
            }
        }
    }
    return result;
}

var allLines = File.ReadAllLines("input");
Console.WriteLine(partOne(allLines));
Console.WriteLine(partTwo(allLines));