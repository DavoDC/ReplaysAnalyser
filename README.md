# Replays Analyser
A C++ console program to analyze SSF2 replays statistically.

I use this program to analyze my autosaved replays: [SSF2 Replays](https://github.com/DavoDC/SSF2Replays).

### Features

#### General
- Reads <ins>replay file names</ins> *only* (doesn't parse replay file content!)
- Automatically determines default replay path by reading username from environment variable.
- Currently exclusive to C++ developers (runs through Visual Studio).

#### Statistics Provided
- Number of replays/matches.
- Date range of matches.
- Percentage and count breakdown of:
    - Game versions used.
    - Years matches were played.
    - Players involved.
    - Characters used in matches.