#!/usr/bin/env python3

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

print(f"v{version_year}.{version_week}.{version_vers}")
