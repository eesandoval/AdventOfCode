var JOKERS_ARE_WILD = false;

var cardRankings = new Dictionary<char, int>
{
    { '2', 1 },
    { '3', 2 },
    { '4', 3 },
    { '5', 4 },
    { '6', 5 },
    { '7', 6 },
    { '8', 7 },
    { '9', 8 },
    { 'T', 9 },
    { 'J', 10 },
    { 'Q', 11 },
    { 'K', 12 },
    { 'A', 13 }
};

int interCardRanking(Tuple<char, int> c1, Tuple<char, int> c2)
{
    if (c1.Item2 != c2.Item2)
        return c1.Item2.CompareTo(c2.Item2) * -1;
    return cardRankings![c1.Item1].CompareTo(cardRankings[c2.Item1]) * -1;
}

int getRanking(string hand)
{
    var tally = hand.GroupBy(c => c).Select(g => new Tuple<char, int>(g.Key, g.Count())).ToList();
    if (JOKERS_ARE_WILD && tally.Where(c => c.Item1 == 'J').Any() && hand != "JJJJJ")
    {
        var totalJokers = tally.Where(c => c.Item1 == 'J').First().Item2;
        tally = tally.Where(h => h.Item1 != 'J').ToList();
        tally.Sort(interCardRanking);
        tally[0] = new Tuple<char, int>(tally[0].Item1, tally[0].Item2 + totalJokers);
    }
    if (tally.Count() == 1) // 1 unique, five of a kind
        return 6;
    if (tally.Count() == 5) // all unique, high card
        return 0;
    if (tally.Where(c => c.Item2 == 4).Any()) // 4 of a kind
        return 5;
    if (tally.Where(c => c.Item2 == 3).Any() && tally.Where(c => c.Item2 == 2).Any()) // full house
        return 4;
    if (tally.Where(c => c.Item2 == 3).Any()) // 3 of a kind
        return 3;
    if (tally.Where(c => c.Item2 == 2).Count() == 2) // 2 pair
        return 2;
    return 1; // default 1 pair
}

int compareHands((string, int) firstHand, (string, int) secondHand)
{
    // -1 -> firstHand is ranked lower
    // 0 -> firstHand == secondHand
    // 1 -> firstHand is ranked higher
    int firstHandType = getRanking(firstHand.Item1), secondHandType = getRanking(secondHand.Item1);
    if (firstHandType != secondHandType)
        return firstHandType.CompareTo(secondHandType);
    for (int i = 0; i < 5; i++)
    {
        if (firstHand.Item1[i] != secondHand.Item1[i])
            return cardRankings![firstHand.Item1[i]].CompareTo(cardRankings[secondHand.Item1[i]]);
    }
    return 0;
}

int playCamelCards(string[] allLines, bool jokers = false)
{
    var result = 0;
    var hands = new List<(string, int)>();
    foreach (var line in allLines)
    {
        hands.Add((line.Split(' ')[0], int.Parse(line.Split(' ')[1])));
    }
    hands.Sort(compareHands);
    for (var i = 1; i <= hands.Count; i++)
    {
        result += hands[i - 1].Item2 * i;
    }
    return result;
}

int partOne(string[] allLines)
{
    return playCamelCards(allLines);
}

int partTwo(string[] allLines)
{
    JOKERS_ARE_WILD = true;
    cardRankings['J'] = 0;
    return playCamelCards(allLines, true);
}

var allLines = File.ReadAllLines("input");
Console.WriteLine(partOne(allLines));
Console.WriteLine(partTwo(allLines));