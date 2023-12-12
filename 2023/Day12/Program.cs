var cache = new Dictionary<(string, List<int>), long>();

long countWays(string springs, List<int> groups)
{
    while (true)
    {
        if (groups.Count == 0)
        {
            return springs.Contains('#') ? 0 : 1;
        }
        if (string.IsNullOrEmpty(springs))
        {
            return 0;
        }
        if (springs.StartsWith('.'))
        {
            springs = springs.Trim('.');
            continue;
        }
        if (springs.StartsWith('?'))
        {
            return calculate("." + springs[1..], groups) + calculate("#" + springs[1..], groups);
        }
        if (springs.StartsWith('#'))
        {
            if (groups.Count == 0 || springs.Length < groups[0] || springs[..groups[0]].Contains('.'))
            {
                return 0;
            }

            if (groups.Count > 1)
            {
                if (springs.Length < groups[0] + 1 || springs[groups[0]] == '#')
                {
                    return 0;
                }

                springs = springs[(groups[0] + 1)..];
                groups = groups.Skip(1).ToList();
                continue;
            }
            springs = springs[groups[0]..];
            groups = groups.Skip(1).ToList();
            continue;
        }
    }
}

long calculate(string springs, List<int> groups)
{
    if (cache!.TryGetValue((springs, groups), out var result))
    {
        return result;
    }
    result = countWays(springs, groups);
    cache[(springs, groups)] = result;
    return result;
}

long partOne(string[] allLines)
{
    long result = 0;
    foreach (var line in allLines)
    {
        var groups = line.Split(' ')[1].Split(',').Select(int.Parse).ToList();
        var springs = line.Split(' ')[0];
        result += calculate(springs, groups);
    }
    return result;
}

long partTwo(string[] allLines)
{
    long result = 0;
    foreach (var line in allLines)
    {
        var groups = line.Split(' ')[1].Split(',').Select(int.Parse).ToList();
        var springs = line.Split(' ')[0];
        springs = string.Join('?', Enumerable.Repeat(springs, 5));
        groups = Enumerable.Repeat(groups, 5).SelectMany(g => g).ToList();
        result += calculate(springs, groups);
    }
    return result;
}

var allLines = File.ReadAllLines("input");
Console.WriteLine(partOne(allLines));
Console.WriteLine(partTwo(allLines));