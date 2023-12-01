var words = new List<string>() {"", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

int partOne(string[] allLines, List<string>? optionalWords = default)
{
    var digitStrings = Enumerable.Range(1, 10)
                                 .Select(d => d.ToString())
                                 .Concat(optionalWords ?? new List<string>())
                                 .ToArray();
    var sum = 0;

    foreach (var line in allLines)
    {
        int minIndex = line.Length, maxIndex = -1;
        string firstDigit = "", lastDigit = "";
        foreach (var digitString in digitStrings)
        {
            var n = line.IndexOf(digitString);
            if (n != -1 && n < minIndex)
            {
                minIndex = n;
                firstDigit = words.Contains(digitString) ? words.FindIndex(x => x == digitString).ToString() : digitString;
            }

            var m = line.LastIndexOf(digitString);
            if (m != -1 && m > maxIndex)
            {
                maxIndex = m;
                lastDigit = words.Contains(digitString) ? words.FindIndex(x => x == digitString).ToString() : digitString;
            }
        }
        int.TryParse(firstDigit + lastDigit, out int final);
        sum += final;
    }
    return sum;
}

int partTwo(string[] allLines)
{    
    return partOne(allLines, words.GetRange(1, words.Count - 1));
}

var allLines = File.ReadAllLines("input");
Console.WriteLine(partOne(allLines));
Console.WriteLine(partTwo(allLines));