int getNewNumber(List<int> history, bool next = true)
{
    var deltas = new List<int>();
    for (var i = 0; i < history.Count - 1; i++)
    {
        deltas.Add(history[i+1] - history[i]);
    }
    if (deltas.Distinct().Count() == 1)
    {
        return history[next ? history.Count - 1 : 0] + deltas[0] * (next ? 1 : -1);
    }
    return history[next ? history.Count - 1 : 0] + getNewNumber(deltas, next) * (next ? 1 : -1);
}

int analyzeHistory(string[] allLines, bool partTwo = false)
{
    var result = 0;
    foreach (var line in allLines)
    {
        var history = line.Split(' ').Select(int.Parse).ToList();
        result += getNewNumber(history, !partTwo);
    }
    return result;
}

int partOne(string[] allLines)
{
    return analyzeHistory(allLines);
}

int partTwo(string[] allLines)
{
    return analyzeHistory(allLines, true);
}

var allLines = File.ReadAllLines("input");
Console.WriteLine(partOne(allLines));
Console.WriteLine(partTwo(allLines));