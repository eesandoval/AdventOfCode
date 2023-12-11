long calculateManhattanDistance((long, long) point1, (long, long) point2)
{
    return Math.Abs(point1.Item1 - point2.Item1) + Math.Abs(point1.Item2 - point2.Item2);
}

List<long> getDistances(string[] allLines, int expansion = 1)
{
    var columnInsertions = new List<int>();
    var rowInsertions = new List<int>();
    // find empty columns
    for (var c = 0; c < allLines[0].Length; c++)
    {
        var allDots = true;
        for (var r = 0; r < allLines.Length; r++)
        {
            if (allLines[r][c] == '#')
            {
                allDots = false;
                break;
            }
        }
        if (allDots)
        {
            columnInsertions.Add(c);
        }
    }
    // find empty rows
    for (var r = 0; r < allLines.Length; r++)
    {
        var allDots = true;
        for (var c = 0; c < allLines[r].Length; c++)
        {
            if (allLines[r][c] == '#')
            {
                allDots = false;
                break;
            }
        }
        if (allDots)
        {
            rowInsertions.Add(r);
        }
    }
    
    var galaxies = new List<(int, int)>();
    var distances = new List<long>();
    for (var r = 0; r < allLines.Length; r++)
    {
        for (var c = 0; c < allLines[r].Length; c++)
        {
            if (allLines[r][c] == '#')
            {
                // as we find galaxies, look backwards from that galaxy and get distances
                foreach (var galaxy in galaxies)
                {
                    var distance = calculateManhattanDistance((c, r), galaxy);
                    // there's two directions when looking back
                    // NW -> the galaxy we look at from r, c has a lower r and lower c
                    // NE -> the galaxy we look at from r, c has a lower r and higher c
                    // regardless, r is always lower
                    // in the case of two galaxies on the same row, r doesn't matter; no insertions
                    distance += rowInsertions.Where(y => galaxy.Item2 < y && y < r).Count() * expansion;
                    if (c > galaxy.Item1) // NW
                    {
                        distance += columnInsertions.Where(x => galaxy.Item1 < x && x < c).Count() * expansion;
                    }
                    else // NE
                    {
                        distance += columnInsertions.Where(x => c < x && x < galaxy.Item1).Count() * expansion;
                    }
                    distances.Add(distance);
                }
                galaxies.Add((c, r));
            }
        }
    }
    return distances;
}

long partOne(string[] allLines)
{
    return getDistances(allLines).Sum();
}

long partTwo(string[] allLines)
{
    return getDistances(allLines, 1000000 - 1).Sum(); // love off by 1 errors
}

var allLines = File.ReadAllLines("input");
Console.WriteLine(partOne(allLines));
Console.WriteLine(partTwo(allLines));