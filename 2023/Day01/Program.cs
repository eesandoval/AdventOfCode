int calibrate(string[] allLines, string[] digitStrings)
{
    Dictionary<string, string> digitConversion = new Dictionary<string, string>();
    digitConversion["one"] = "1";
    digitConversion["two"] = "2";
    digitConversion["three"] = "3";
    digitConversion["four"] = "4";
    digitConversion["five"] = "5";
    digitConversion["six"] = "6";
    digitConversion["seven"] = "7";
    digitConversion["eight"] = "8";
    digitConversion["nine"] = "9";
    int sum = 0;

    foreach (var line in allLines)
    {
        int minIndex = line.Length, maxIndex = -1;
        string firstDigit = "", lastDigit = "";
        foreach (var digitString in digitStrings)
        {
            int n = line.IndexOf(digitString);
            if (n != -1 && n < minIndex)
            {
                minIndex = n;
                firstDigit = digitConversion.ContainsKey(digitString) ? digitConversion[digitString] : digitString;
            }

            int m = line.LastIndexOf(digitString);
            if (m != -1 && m > maxIndex)
            {
                maxIndex = m;
                lastDigit = digitConversion.ContainsKey(digitString) ? digitConversion[digitString] : digitString;
            }
        }
        int.TryParse(firstDigit + lastDigit, out int final);
        sum += final;
    }
    return sum;
}

int partOne(string[] allLines)
{
    string[] digitStrings = {"1", "2", "3", "4", "5", "6", "7", "8", "9"};
    return calibrate(allLines, digitStrings);
}

int partTwo(string[] allLines)
{
    string[] digitStrings = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    return calibrate(allLines, digitStrings);
}

var allLines = File.ReadAllLines("input");
Console.WriteLine(partOne(allLines));
Console.WriteLine(partTwo(allLines));