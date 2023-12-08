using System.Text.RegularExpressions;

var node = new Regex(@"(\w+)", RegexOptions.Compiled);

Dictionary<string, string> createNetwork(string[] allLines)
{
    var network = new Dictionary<string, string>();
    foreach (var line in allLines.Skip(2))
    {
        var n = node!.Matches(line).Select(m => m.Groups[0].Value).ToList();
        network[n[0] + "L"] = n[1];
        network[n[0] + "R"] = n[2];
    }
    return network;
}

int partOne(string[] allLines)
{
    var instructions = allLines[0];
    var network = createNetwork(allLines);
    var currentNode = "AAA";
    var i = 0;
    while (currentNode != "ZZZ")
    {
        currentNode = network[currentNode + instructions[i++ % instructions.Length].ToString()];
    }
    return i;
}

long greatestCommonDivisor(long a, long b)
{
    return b == 0 ? a : greatestCommonDivisor(b, a % b);
}

long leastCommonMultiple(long a, long b)
{
    return Math.Abs(a * b) / greatestCommonDivisor(a, b);
}

long partTwo(string[] allLines)
{
    var instructions = allLines[0];
    var network = createNetwork(allLines);
    var currentNodes = new List<string>();
    foreach (var line in allLines.Skip(2))
    {
        var n = node!.Matches(line).Select(m => m.Groups[0].Value).First();
        if (n.EndsWith('A'))
        {
            currentNodes.Add(n);
        }
    }

    // based on the example, a cycle develops:
    // 11A goes to 11Z every 2 steps
    // 22A goes to 22Z every 3 steps
    // lcm(2,3) -> 6
    // in theory, if we check how many steps each node takes to get to
    // a node ending in Z, we can take the LCM of them all to get a final answer
    var steps = Enumerable.Repeat(0, currentNodes.Count).Select(x => (long)x).ToList();
    for (var i = 0; i < currentNodes.Count; i++)
    {
        while (!currentNodes[i].EndsWith('Z'))
        {
            currentNodes[i] = network[currentNodes[i] + instructions[(int)steps[i]++ % instructions.Length].ToString()];
        }
    }
    return steps.Aggregate(leastCommonMultiple);
}

var allLines = File.ReadAllLines("input");
Console.WriteLine(partOne(allLines));
Console.WriteLine(partTwo(allLines));