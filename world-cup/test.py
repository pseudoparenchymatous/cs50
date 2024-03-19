import csv
import sys

teams = []
with open("2018m.csv", "r") as file:
    reader = csv.DictReader(file)
    for row in reader:
        team = {
            "team": row["team"],
            "rating": int(row["rating"])
        }
        teams.append(team)

counts = {}
ii = 0
for i in teams:
    name = i["team"]
    counts[name] = 0
