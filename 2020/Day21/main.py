from re import match
from collections import OrderedDict


def parse_input(lines):
    p_allergens = {}
    all_ingredients = {}
    for line in lines:
        food = match(r"([a-z\s]+)\s\(contains\s([a-z,\s]+)\)", line)
        ingredients, allergens = food.groups()
        ingredients = set(ingredients.split(' '))
        for allergen in allergens.split(','):
            allergen = allergen.strip()
            if allergen in p_allergens:
                p_ingredients = p_allergens[allergen]
            else:
                p_ingredients = ingredients
            p_allergens[allergen] = p_ingredients.intersection(ingredients)
        for ingredient in ingredients:
            if ingredient in all_ingredients:
                all_ingredients[ingredient] += 1
            else:
                all_ingredients[ingredient] = 1
    return p_allergens, all_ingredients


def part_one(p_allergens, all_ingredients):
    bad_ingredients = set()
    for ingredient in p_allergens.values():
        bad_ingredients = bad_ingredients.union(ingredient)
    for ingredient in bad_ingredients:
        all_ingredients[ingredient] = 0
    return sum(all_ingredients.values())


def part_two(p_allergens, all_ingredients):
    has_duplicates = True
    while has_duplicates:
        has_duplicates = False
        for allergen, ingredients in p_allergens.items():
            if len(ingredients) == 1:
                ingredient = next(iter(ingredients))
                for sub_allergen in p_allergens:
                    if sub_allergen == allergen:
                        continue
                    if ingredient in p_allergens[sub_allergen]:
                        p_allergens[sub_allergen].remove(ingredient)
                        has_duplicates = True
    result = []
    ordered_p_allergens = OrderedDict(sorted(p_allergens.items()))
    for allergen, ingredients in ordered_p_allergens.items():
        result.append(next(iter(ingredients)))
    return ','.join(result)


with open("input.txt", "r") as f:
    lines = f.read().splitlines()
    p_allergens, all_ingredients = parse_input(lines)
    print(part_one(p_allergens, all_ingredients))
    print(part_two(p_allergens, all_ingredients))
