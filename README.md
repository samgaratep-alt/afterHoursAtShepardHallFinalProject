
# After Hours at Shepard Hall

A C++ text based horror adventure game set in Shepard Hall, where strange notes and failing lights lead the player through a hidden portal into a dark fantasy world.

## Overview

After Hours at Shepard Hall is a branching text adventure written in C++. The player begins alone in Shepard Hall late at night, where unsettling notes, dark hallways, and impossible spaces lead deeper into the building. What begins as a strange night on campus turns into a journey through a hidden portal and into a dark fantasy world filled with danger, mystery, and multiple possible outcomes.

The game combines horror atmosphere, branching choices, item collection, role selection, health based consequences, and multiple endings.

## Features

- Branching story choices
- Multiple player roles:
  - Knight
  - Scholar
  - Peasant
- Inventory system
- Health system
- Location based progression
- Dragon encounter minigame using randomness
- Multiple endings
- Atmospheric timed pauses for suspense
- ASCII art elements

## Project Structure

- `main.cpp` — starts the game
- `game.cpp` — main game logic and story flow
- `game.h` — game class declarations
- `player.cpp` — player class functions
- `player.h` — player class declarations
- `location.cpp` — location class functions and location data
- `location.h` — location class declarations

## How to Compile and Run

Compile with:

```bash      
g++ main.cpp game.cpp player.cpp location.cpp -std=c++17 -o game.exe
