using System.Text.RegularExpressions;

var numbers = new Regex(@"(\d+)", RegexOptions.Compiled);

List<long> regexToList(string line)
{
    return numbers.Matches(line).Cast<Match>().Select(match => long.Parse(match.Value)).ToList();
}

long partOne(string[] allLines)
{
    var seeds = regexToList(allLines[0]);
    for (var i = 3; i < allLines.Length; i += 2)
    {
        var mappings = new List<(long, long, long)>();
        while (i < allLines.Length && allLines[i].Trim() != "")
        {
            var map = regexToList(allLines[i++]);
            mappings.Add((map[0], map[1], map[2]));
        }
        for (int j = 0; j < seeds.Count; j++)
        {
            foreach (var mapping in mappings)
            {
                if (mapping.Item2 <= seeds[j] && seeds[j] <= mapping.Item2 + mapping.Item3) // between start and start + range
                {
                    seeds[j] = mapping.Item1 + seeds[j] - mapping.Item2;
                    break;
                }
            }
        }
    }
    return seeds.Min();
}

long partTwo(string[] allLines)
{   
    var initSeeds = regexToList(allLines[0]);
    var allMappings = new List<List<(long, long, long)>>();
    for (var i = 3; i < allLines.Length; i += 2)
    {
        var mappings = new List<(long, long, long)>();
        while (i < allLines.Length && allLines[i].Trim() != "")
        {
            var map = regexToList(allLines[i++]);
            mappings.Add((map[0], map[1], map[2]));
        }
        allMappings.Add(mappings);
    }

    var outputs = new List<(long, long)>();
    for (int i = 0; i < initSeeds.Count; i += 2)
    {
        var ranges = new Stack<(long, long)>();
        var results = new Stack<(long, long)>();
        ranges = new Stack<(long, long)>(ranges.Append((initSeeds[i], initSeeds[i] + initSeeds[i + 1])));
        foreach (var mappings in allMappings)
        {
            while (ranges.Count > 0)
            {
                var startStop = ranges.Pop();
                var loopBreak = false;
                foreach (var mapping in mappings)
                {
                    var end = mapping.Item2 + mapping.Item3;
                    var offset = mapping.Item1 - mapping.Item2;
                    if (end <= startStop.Item1 || startStop.Item2 <= mapping.Item2)
                    {
                        continue;
                    }
                    if (startStop.Item1 < mapping.Item2)
                    {
                        ranges = new Stack<(long, long)>(ranges.Append((startStop.Item1, mapping.Item2)));
                        startStop.Item1 = mapping.Item2;
                    }
                    if (end < startStop.Item2)
                    {
                        ranges = new Stack<(long, long)>(ranges.Append((end, startStop.Item2)));
                        startStop.Item2 = end;
                    }
                    results = new Stack<(long, long)>(results.Append((startStop.Item1 + offset, startStop.Item2 + offset)));
                    loopBreak = true;
                    break;
                }
                if (!loopBreak)
                {
                    results = new Stack<(long, long)>(results.Append((startStop.Item1, startStop.Item2)));
                }
            }
            ranges = results;
            results = new Stack<(long, long)>();
        }
        outputs.AddRange(ranges);
    }
    return outputs.OrderBy(x => x.Item1).First().Item1;
}

var allLines = File.ReadAllLines("input");
Console.WriteLine(partOne(allLines));
Console.WriteLine(partTwo(allLines));