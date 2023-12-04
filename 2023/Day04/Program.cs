using System.Text.RegularExpressions;

var numbers = new Regex(@"(\d+)", RegexOptions.Compiled);

int calculateMatches(string scratchCard)
{
    scratchCard = scratchCard.Split(':')[1];
    var matches = numbers.Matches(scratchCard.Split('|')[0]);
    var winningNumbers = new HashSet<int>();
    foreach (Match m in matches)
    {
        int.TryParse(m.Groups[0].Value, out int n);
        winningNumbers.Add(n);
    }

    matches = numbers.Matches(scratchCard.Split('|')[1]);
    var scratchedNumbers = new HashSet<int>();
    foreach (Match m in matches)
    {
        int.TryParse(m.Groups[0].Value, out int n);
        scratchedNumbers.Add(n);
    }
    return winningNumbers.Intersect(scratchedNumbers).Count();

}

int partOne(string[] allLines)
{
    var result = 0;
    foreach (var line in allLines)
    {
        var wins = calculateMatches(line);
        if (wins == 0)
            continue;
        result += (int)Math.Pow(2, wins - 1);
    }
    return result;
}

int partTwo(string[] allLines)
{
    var scratchCardCopies = Enumerable.Range(1, allLines.Length).Select(x => 1).ToList();
    for (var i = 0; i < allLines.Length; i++)
    {
        var wins = calculateMatches(allLines[i]);
        for (var j = 1; j <= wins; j++)
        {
            scratchCardCopies[i + j] += scratchCardCopies[i];
        }
    }
    return scratchCardCopies.Sum();
}

var allLines = File.ReadAllLines("input");
Console.WriteLine(partOne(allLines));
Console.WriteLine(partTwo(allLines));