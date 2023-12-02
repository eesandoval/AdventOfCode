using System.Text.RegularExpressions;

var rxGame = new Regex(@"Game (\d+)", RegexOptions.Compiled);
var rxCubes = new Regex(@"(\d+) (\w+)", RegexOptions.Compiled);

int partOne(string[] allLines)
{
    int result = 0;
    var maxCubes = new Dictionary<string, int>
    {
        ["red"] = 12,
        ["green"] = 13,
        ["blue"] = 14
    };
    foreach (var line in allLines)
    {
        var validGame = true;
        int.TryParse(rxGame.Match(line).Groups[1].Value, out int ID);
        var cubeMatches = rxCubes.Matches(line);
        foreach (Match cube in cubeMatches)
        {
            int.TryParse(cube.Groups[1].Value, out int number);
            string color = cube.Groups[2].Value;
            if (maxCubes[color] < number)
            {
                validGame = false;
                break;
            }
        }
        if (validGame)
            result += ID;
    }
    return result;
}

int partTwo(string[] allLines)
{
    int result = 0;
    foreach (var line in allLines)
    {
        var cubes = new Dictionary<string, int>
        {
            ["red"] = 0,
            ["blue"] = 0,
            ["green"] = 0
        };
        int.TryParse(rxGame.Match(line).Groups[1].Value, out int ID);
        var cubeMatches = rxCubes.Matches(line);
        foreach (Match cube in cubeMatches)
        {
            int.TryParse(cube.Groups[1].Value, out int number);
            string color = cube.Groups[2].Value;
            cubes[color] = Math.Max(cubes[color], number);
        }
        result += cubes["red"] * cubes["blue"] * cubes["green"];
    }
    return result;
}

var allLines = File.ReadAllLines("input");
Console.WriteLine(partOne(allLines));
Console.WriteLine(partTwo(allLines));