# GTA IV LS Gang Expansion — C++17 starter

A BudgieOS/BNU example project for organizing an original Los Santos-inspired faction and district data pack for **GTA IV PC**.

## What this project currently does
- Uses C++17, matching BNU's language baseline.
- Loads faction and district labels from `config/gangs.ini`.
- Validates entries and prints a readable summary.
- Keeps game-specific integration isolated for a later GTA IV scripting adapter.

## Factions in the sample
- Grove Street Families
- Ballas
- Los Santos Vagos

## Build the standalone data tool
From this directory:

```sh
cmake -S . -B build
cmake --build build --config Release
./build/ls_gang_data
```

On Windows, run `build\\Release\\ls_gang_data.exe` (or the executable path produced by your generator).

## BNU relationship
This is a C++ example under the BNU repository. BNU is a native utilities toolkit, **not** a GTA IV mod loader or game SDK. The project does not currently inject into GTA IV or alter the game.

## Next integration step
To make a loadable GTA IV PC plugin, add a small adapter for a ScriptHook/ASI SDK version that matches the installed GTA IV build. That SDK is not bundled here; do not copy DLLs from random downloads. The adapter will map this project's faction data to supported in-game UI and world APIs.

## Scope and limits
- This is source code, not a compiled `.asi` plugin.
- It does not add weapons, combat behavior, character models, textures, or blood effects.
- District names are labels only; they do not create a 210 km² map. A map expansion needs original map assets and engine-specific streaming work.
- No Rockstar game files or assets are included.
