card = {}
card["number"] = "1234"
card["length"] = len(card["number"])
print(card)
card["digits"] = []
for i in card["number"]:
    card["digits"] += (i)

print(card["number"][0])
print(card["number"][1])
print(card["number"][2])