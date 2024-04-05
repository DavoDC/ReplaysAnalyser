# Replays Analyser
A C++ console program to analyse [Super Smash Flash 2](https://mcleodgaming.fandom.com/wiki/Super_Smash_Flash_2) (SSF2) replays statistically.

I use this program to analyse my autosaved replays, which can be found here: [SSF2 Replays](https://github.com/DavoDC/SSF2Replays).

### Features

#### General
- Reads <ins>replay file names</ins> *only* (doesn't parse replay file content!).
- Automatically determines default replay path.
- Currently exclusive to C++ developers (runs through Visual Studio).

#### Statistics Provided
- Number of replays/matches.
- Date range of matches, time period in-between, and time passed since the last match.
- Percentage, count, date range, time period and time passed breakdowns of:
    - Game versions used.
    - Years matches were played.
    - Players involved.
    - Characters used in matches.
