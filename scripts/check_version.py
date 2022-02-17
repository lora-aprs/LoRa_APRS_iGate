#!/usr/bin/env python3

from datetime import date

today = date.today()

current_year = int(str(today.isocalendar()[0])[2:])
current_week = int(today.isocalendar()[1])

version = None
with open("src/LoRa_APRS_iGate.cpp") as f:
    for line in f:
        if line.startswith("#define VERSION"):
            version = line.strip().split(" ")[2].replace('"', "")

version_split = version.split(".")
version_year = int(version_split[0])
version_week = int(version_split[1])

print(f"firmware version year: {version_year}")
print(f"firmware version week: {version_week}")

print(f"current year: {current_year}")
print(f"current week: {current_week}")

error = False
if version_year != current_year:
    print("firmware version is not current year!")
    error = True

if version_week != current_week:
    print("firmware version is not current week!")
    error = True

exit(error)
