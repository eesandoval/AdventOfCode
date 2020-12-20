import collections

sea_monster = [
    (0, 18),
    (1, 0),
    (1, 5),
    (1, 6),
    (1, 11),
    (1, 12),
    (1, 17),
    (1, 18),
    (1, 19),
    (2, 1),
    (2, 4),
    (2, 7),
    (2, 10),
    (2, 13),
    (2, 16)
]


def extract_sides(tile):
    up = tile[0]
    down = tile[-1]
    left = "".join(sub_t[0] for sub_t in tile)
    right = "".join(sub_t[-1] for sub_t in tile)
    return up, down, left, right


def get_image(tile):
    return list(sub_t[1:-1] for sub_t in tile[1:-1])


def find_matching(tiles, edges, id, side):
    our_tile = tiles[id]
    to_match = our_tile[side]
    matches = edges[to_match].copy()
    matches.remove(id)
    if len(matches) < 1:
        return
    match = matches[0]
    that_tile = tiles[match]
    if side == "up":
        other_side = "down"
    elif side == "down":
        other_side = "up"
    elif side == "left":
        other_side = "right"
    elif side == "right":
        other_side = "left"

    if to_match != that_tile[other_side]:
        t = that_tile.copy()
        for _ in range(4):
            for _ in range(2):
                for _ in range(2):
                    if to_match == t[other_side]:
                        tiles[match] = t
                        return match

                    temp = t["left"]
                    t["left"] = t["right"]
                    t["right"] = temp
                    t["up"] = t["up"][::-1]
                    t["down"] = t["down"][::-1]
                    t["image"] = [row[::-1] for row in t["image"]]

                temp = t["up"]
                t["up"] = t["down"]
                t["down"] = temp
                t["left"] = t["left"][::-1]
                t["right"] = t["right"][::-1]
                t["image"] = t["image"][::-1]

            up = t["up"]
            down = t["down"]
            left = t["left"]
            right = t["right"]

            t["right"] = up
            t["down"] = right[::-1]
            t["left"] = down
            t["up"] = left[::-1]

            t["image"] = ["".join(list(x)[::-1]) for x in zip(*t["image"])]
    return match


def stich_image(tiles, edges, top_left):
    image = []
    row = [top_left]
    current = top_left

    while True:
        image.append(row)
        while True:
            matched = find_matching(tiles, edges, current, "right")
            if matched is None:
                break
            else:
                row.append(matched)
                current = matched
        current = find_matching(tiles, edges, row[0], "down")
        if current is None:
            break
        row = [current]

    full_image = []
    for row in image:
        tiles_in_row = [tiles[col] for col in row]
        for i in range(len(tiles_in_row[0]["image"])):
            full_image.append("".join(tile["image"][i]
                              for tile in tiles_in_row))
    return full_image


def monster_count(image):
    monsters = 0
    for y in range(len(image) - 3):
        for x in range(len(image[0]) - 20):
            found = True
            for yi, xi in sea_monster:
                if image[y + yi][x + xi] != '#':
                    found = False
                    break
            if found:
                monsters += 1
    return monsters


def part_one(lines):
    tiles = {}
    edges = []
    for line in lines:
        tile_info = line.splitlines()
        name = tile_info[0]
        tile = tile_info[1:]
        tile_id = int(name.split(" ")[1][:-1])
        up, down, left, right = extract_sides(tile)
        tiles[tile_id] = {"up": up, "down": down, "left": left, "right": right}
        edges.append(up)
        edges.append(up[::-1])
        edges.append(down)
        edges.append(down[::-1])
        edges.append(left)
        edges.append(left[::-1])
        edges.append(right)
        edges.append(right[::-1])
    edge_count = collections.Counter(edges)
    unique_edges = set(edge for edge, n in edge_count.items() if n == 1)
    result = 1
    for num, tile in tiles.items():
        unmatched = 0
        if tile["up"] in unique_edges:
            unmatched += 1
        if tile["down"] in unique_edges:
            unmatched += 1
        if tile["left"] in unique_edges:
            unmatched += 1
        if tile["right"] in unique_edges:
            unmatched += 1
        if unmatched == 2:
            result *= num
    return result


def part_two(lines):
    tiles = {}
    edges = collections.defaultdict(list)
    for line in lines:
        tile_info = line.splitlines()
        name = tile_info[0]
        tile = tile_info[1:]
        tile_id = int(name.split(" ")[1][:-1])
        up, down, left, right = extract_sides(tile)
        image = get_image(tile)
        tiles[tile_id] = {"up": up, "down": down, "left": left,
                          "right": right, "image": image}
        edges[up].append(tile_id)
        edges[up[::-1]].append(tile_id)
        edges[down].append(tile_id)
        edges[down[::-1]].append(tile_id)
        edges[left].append(tile_id)
        edges[left[::-1]].append(tile_id)
        edges[right].append(tile_id)
        edges[right[::-1]].append(tile_id)
    edge_count = {edge: len(tiles) for edge, tiles in edges.items()}
    unique_edges = set(edge for edge, n in edge_count.items() if n == 1)

    top_left = None
    for num, tile in tiles.items():
        if tile["up"] in unique_edges and tile["left"] in unique_edges:
            top_left = num
            break
    image = stich_image(tiles, edges, top_left)
    hash_count = "".join(image).count('#')
    for _ in range(4):
        for _ in range(2):
            for _ in range(2):
                c = hash_count - monster_count(image) * len(sea_monster)
                if c < hash_count:
                    return c
                image = [row[::-1] for row in image]
            image = image[::-1]
        image = ["".join(list(x)[::-1]) for x in zip(*image)]
    return 0


with open("input.txt", "r") as f:
    lines = f.read().split('\n\n')
    print(part_one(lines))
    print(part_two(lines))
