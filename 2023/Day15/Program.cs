using System.Collections.Specialized;
using System.Text.RegularExpressions;

long partOne(string[] allLines)
{
    long result = 0;
    var hashes = allLines[0].Split(',');
    foreach (var hash in hashes)
    {
        var currentValue = 0;
        foreach (var c in hash)
        {
            currentValue += c;
            currentValue *= 17;
            currentValue %= 256;
        }
        result += currentValue;
    }
    return result;
}

long partTwo(string[] allLines)
{
    long result = 0;
    var number = new Regex(@"(\d+)");
    var word = new Regex(@"(\w+)");
    var hashes = allLines[0].Split(',');
    var boxes = new List<OrderedDictionary>();
    for (var i = 0; i < 256; i++)
    {
        boxes.Add(new OrderedDictionary());
    }
    
    foreach (var hash in hashes)
    {
        var currentValue = 0;
        foreach (var c in hash)
        {
            if (c == '=' || c == '-')
                break;
            currentValue += c;
            currentValue *= 17;
            currentValue %= 256;
        }
        var label = word.Match(hash).Groups[1].ToString();
        if (hash.Contains('='))
        {
            var focal = int.Parse(number.Match(hash).Groups[1].ToString());
            boxes[currentValue][label] = focal;
        }
        else
        {
            boxes[currentValue].Remove(label);
        }
    }
    for (var box = 0; box < boxes.Count; box++)
    {
        var lenNumber = 1;
        foreach (var k in boxes[box].Keys)
        {
            result += (1 + box) * lenNumber++ * (int)boxes[box][k];
        }
    }
    return result;
}

var allLines = File.ReadAllLines("input");
Console.WriteLine(partOne(allLines));
Console.WriteLine(partTwo(allLines));