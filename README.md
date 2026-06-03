# Replays Analyser

[![ko-fi](https://ko-fi.com/img/githubbutton_sm.svg)](https://ko-fi.com/G2G31WKOCN)



A C++ console program to analyse [Super Smash Flash 2](https://mcleodgaming.fandom.com/wiki/Super_Smash_Flash_2) (SSF2) replays statistically.

I use this program to analyse my autosaved replays, which can be found here: [SSF2 Replays](https://github.com/DavoDC/SSF2Replays).

## Build & Run

> **Windows only.** Requires Visual Studio with C++ workload.

1. Open `Project/ReplaysAnalyser.sln` in Visual Studio
2. Build with **Ctrl+Shift+B**
3. Run with **F5** - the program auto-detects your SSF2 replay folder

### Features

#### General
- Reads <ins>replay file names</ins> *only* (doesn't parse replay file content!).
- Automatically determines default replay path.
- Windows only (runs through Visual Studio).

#### Statistics Provided
- Total number of matches.
- Percentage and count breakdowns of matches based on:
    - Game versions used.
    - Years matches were played.
    - Players involved.
    - Characters used in matches.
- Date statistics for all matches and the four properties above:
    - Date of first match (and timed passed since).
    - Date of last match (and timed passed since).
    - Time period in-between.
- Player-specific character statistics.
    - Top three characters for top players.

## Tech

- **Language:** C++
- **IDE:** Visual Studio (Windows only)
- Reads replay filenames only - no binary parsing required

## Development

**Developed:** March 2023