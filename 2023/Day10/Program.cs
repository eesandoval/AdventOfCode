Dictionary<(int, int), int> getDistances(string[] allLines)
{
    var pipes = new Dictionary<(int, int), List<(int, int)>>();
    var distances = new Dictionary<(int, int), int>();
    var start = (0, 0);
    for (var r = 0; r < allLines.Length; r++)
    {
        for (var c = 0; c < allLines[r].Length; c++)
        {
            if (allLines[r][c] == 'S') // assume it's F
            {
                start = (r, c);
            }
            if (allLines[r][c] == '|') // up and down
            {
                pipes[(r, c)] = new List<(int, int)>()
                {
                    (r+1, c),
                    (r-1, c)
                };
            }
            else if (allLines[r][c] == '-') // left and right
            {
                pipes[(r, c)] = new List<(int, int)>()
                {
                    (r, c+1),
                    (r, c-1)
                };
            }
            else if (allLines[r][c] == 'L') // up and right
            {
                pipes[(r, c)] = new List<(int, int)>()
                {
                    (r-1, c),
                    (r, c+1)
                };
            }
            else if (allLines[r][c] == 'J') // up and left
            {
                pipes[(r, c)] = new List<(int, int)>()
                {
                    (r-1, c),
                    (r, c-1)
                };
            }
            else if (allLines[r][c] == '7') // down and left
            {
                pipes[(r, c)] = new List<(int, int)>()
                {
                    (r+1, c),
                    (r, c-1)
                };
            }
            else if (allLines[r][c] == 'F' || allLines[r][c] == 'S') // down and right
            {
                pipes[(r, c)] = new List<(int, int)>()
                {
                    (r+1, c),
                    (r, c+1)
                };
            }
            else // .
            {
                pipes[(r, c)] = new List<(int, int)>();
            }
            distances[(r, c)] = -1;
        }
    }

    // DFS store distances in an a dictionary for each step, overwriting the -1
    var queue = new Queue<(int, int)>();
    queue.Enqueue(start);
    var explored = new HashSet<(int, int)>
    {
        start
    };
    distances[start] = 0;
    while (queue.Count > 0)
    {
        var next = queue.Dequeue();
        foreach (var edge in pipes[next])
        {
            if (!explored.Contains(edge))
            {
                explored.Add(edge);
                queue.Enqueue(edge);
                distances[edge] = distances[next] + 1;
            }
        }
    }

    // Remove anything not part of the main loop for part 2
    foreach (var d in distances.Keys)
    {
        if (distances[d] == -1)
        {
            distances.Remove(d);
            pipes.Remove(d);
        }
    }
    return distances;
}

int partOne(string[] allLines)
{
    return getDistances(allLines).Max(x => x.Value);
}

int partTwo(string[] allLines)
{
    var distances = getDistances(allLines);
    var upscaledGrid = new List<List<char>>();
    // Expand the grind by 3x3
    for (int i = 0; i < allLines.Length * 3; i++)
    {
        var row = new List<char>();
        for (int j = 0; j < allLines[0].Length * 3; j++)
        {
            row.Add(' ');
        }
        upscaledGrid.Add(row);
    }
    for (var r = 0; r < allLines.Length; r++)
    {
        var row = new List<char>();
        for (var c = 0; c < allLines[r].Length; c++)
        {
            if (distances.ContainsKey((r, c)))
            {
                switch (allLines[r][c])
                {
                    case '|':
                        upscaledGrid[r*3][c*3 + 1] = '|';
                        upscaledGrid[r*3 + 1][c*3 + 1] = '|'; // center
                        upscaledGrid[r*3 + 2][c*3 + 1] = '|';
                        break;
                    case '-':
                        upscaledGrid[r*3 + 1][c*3] = '-';
                        upscaledGrid[r*3 + 1][c*3 + 1] = '-'; // center
                        upscaledGrid[r*3 + 1][c*3 + 2] = '-';
                        break;
                    case 'L':
                        upscaledGrid[r*3][c*3 + 1] = '|';
                        upscaledGrid[r*3 + 1][c*3 + 1] = 'L'; // center
                        upscaledGrid[r*3 + 1][c*3 + 2] = '-';
                        break;
                    case 'J':
                        upscaledGrid[r*3][c*3 + 1] = '|';
                        upscaledGrid[r*3 + 1][c*3 + 1] = 'J'; // center
                        upscaledGrid[r*3 + 1][c*3] = '-';
                        break;
                    case '7':
                        upscaledGrid[r*3 + 1][c*3] = '-';
                        upscaledGrid[r*3 + 1][c*3 + 1] = '7'; // center
                        upscaledGrid[r*3 + 2][c*3 + 1] = '|';
                        break;
                    case 'F':
                        upscaledGrid[r*3 + 1][c*3 + 2] = '-';
                        upscaledGrid[r*3 + 1][c*3 + 1] = 'F'; // center
                        upscaledGrid[r*3 + 2][c*3 + 1] = '|';
                        break;
                    case 'S': // I didn't account that S is a + and the last example had a hole when expanded...
                        upscaledGrid[r*3][c*3 + 1] = '|';
                        upscaledGrid[r*3 + 2][c*3 + 1] = '|';
                        upscaledGrid[r*3 + 1][c*3 + 1] = 'S'; // center
                        upscaledGrid[r*3 + 1][c*3] = '-';
                        upscaledGrid[r*3 + 1][c*3 + 2] = '-';
                        break;
                }
            }
            else
            {
                // If it's not part of the main loop, expand it as a potential I(nside)
                // Around an I is just empty space that may be filled later
                upscaledGrid[r*3 + 1][c*3 + 1] = 'I';   
            }
        }
    }

    // Use DFS to fill starting from the top left corner (0, 0)
    var queue = new Queue<(int, int)>();
    queue.Enqueue((0, 0));
    var explored = new HashSet<(int, int)>()
    {
        (0, 0)
    };
    while (queue.Count > 0)
    {
        var n = queue.Dequeue();
        // Avoid replacing the main loop itself; only blanks and I
        if (upscaledGrid[n.Item1][n.Item2] == ' ' || upscaledGrid[n.Item1][n.Item2] == 'I')
        {
            upscaledGrid[n.Item1][n.Item2] = 'O';
            if (n.Item1 - 1 > 0 && !explored.Contains((n.Item1 - 1, n.Item2)))
            {
                queue.Enqueue((n.Item1 - 1, n.Item2));
            }
            if (n.Item1 + 1 < upscaledGrid.Count && !explored.Contains((n.Item1 + 1, n.Item2)))
            {
                queue.Enqueue((n.Item1 + 1, n.Item2));
            }
            if (n.Item2 - 1 > 0 && !explored.Contains((n.Item1, n.Item2 - 1)))
            {
                queue.Enqueue((n.Item1, n.Item2 - 1));
            }
            if (n.Item2 + 1 < upscaledGrid[0].Count && !explored.Contains((n.Item1, n.Item2 + 1)))
            {
                queue.Enqueue((n.Item1, n.Item2 + 1));
            }
        }
    }
    // Count instances of I that we initially placed and haven't been overwritten
    return upscaledGrid.SelectMany(x => x).Count(y => y == 'I');
}

var allLines = File.ReadAllLines("input");
Console.WriteLine(partOne(allLines));
Console.WriteLine(partTwo(allLines));