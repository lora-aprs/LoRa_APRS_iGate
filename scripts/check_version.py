#!/usr/bin/env python3

import git
from datetime import date

today = date.today()

current_year = int(str(today.isocalendar()[0])[2:])
current_week = int(today.isocalendar()[1])

version = None
with open("src/LoRa_APRS_iGate.cpp") as f:
    for line in f:
        if line.startswith("#define VERSION"):
            version = line.strip().split(" ")[-1].replace('"', "")

version_split = version.split(".")
version_year = int(version_split[0])
version_week = int(version_split[1])
version_vers = int(version_split[2])

print(f"[INFO] firmware version year: {version_year}")
print(f"[INFO] firmware version week: {version_week}")
print(f"[INFO] firmware version version: {version_vers}")
print(f"[INFO] -> {version}")

print(f"[INFO] current year: {current_year}")
print(f"[INFO] current week: {current_week}")
print(f"[INFO] -> {current_year}.{current_week}.x")

error = False
if version_year != current_year:
    print("[ERROR] firmware version is not current year!")
    error = True

if version_week != current_week:
    print("[ERROR] firmware version is not current week!")
    error = True

repo = git.Repo('.')
if f"v{version}" in repo.tags:
    print("[ERROR] tag with this version is already existing")
    error = True

if error:
    print("[ERROR] check/update VERSION define in src/LoRa_APRS_iGate.cpp to fix this issue")

exit(error)
