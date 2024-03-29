﻿using System.Text.RegularExpressions;

var numbers = new Regex(@"(\d+)", RegexOptions.Compiled);

int getNumberOfWins(long time, long distance)
{
    var hold = 1; // holding for 0 makes no sense
    while ((time - hold) * hold++ <= distance);
    return (int)(time + 1 - (hold - 1) * 2); // symmetrical, remove sides
}

int partOne(string[] allLines)
{
    var result = 1;
    var times = new List<int>(numbers.Matches(allLines[0]).Select(m => int.Parse(m.Groups[0].Value)));
    var distances = new List<int>(numbers.Matches(allLines[1]).Select(m => int.Parse(m.Groups[0].Value)));
    for (var i = 0; i < times.Count; i++)
    {
        result *= getNumberOfWins(times[i], distances[i]);
    }
    return result;
}

int partTwo(string[] allLines)
{
    var time = long.Parse(string.Join("", numbers.Matches(allLines[0]).Select(m => m.Groups[0].Value.ToString())));
    var distance = long.Parse(string.Join("", numbers.Matches(allLines[1]).Select(m => m.Groups[0].Value.ToString())));
    return getNumberOfWins(time, distance);
}

var allLines = File.ReadAllLines("input");
Console.WriteLine(partOne(allLines));
Console.WriteLine(partTwo(allLines));