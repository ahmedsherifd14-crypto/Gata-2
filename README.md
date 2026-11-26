# San Clemente — Playable UE5 Foundation (v0.2)

This package is a source-code foundation for an original open-world action game. It is not the full AAA game and does not include licensed/finished art, voice acting, a completed three-city world, 30 story missions, aircraft, boats, advanced police AI, or a tested packaged build.

## Included
- UE 5.4 C++ project structure
- Runtime-generated blockout neighborhood (roads/buildings made from engine primitive meshes)
- Third-person character with camera, walk, sprint, jump, crouch
- Simple drivable vehicle pawn and enter/exit interaction
- Three checkpoint triggers and money rewards
- Basic HUD with money, objective and wanted stars
- F6 increments wanted level for system testing
- Save-game data/subsystem can be added/expanded in the next milestone

## Controls
WASD movement / vehicle controls, mouse camera, Space jump, Left Shift sprint, Left Ctrl crouch, E enter/exit vehicle, F6 wanted-level test.

## Open on Windows
1. Install Unreal Engine 5.4 and Visual Studio 2022 with Game development with C++.
2. Right-click `SanClemente.uproject` → Generate Visual Studio project files.
3. Build `SanClementeEditor` in Development Editor / Win64.
4. Open the `.uproject` in Unreal Editor.
5. In Unreal Editor, create a Basic level and save it as `/Game/Maps/Map_Start`.
6. Add a `PlayerStart` actor near the origin (0, 0, 100), then set this map as both the Game Default Map and Editor Startup Map in Project Settings → Maps & Modes.
7. Press Play. The GameMode creates a blockout city at runtime.

## Important build notes
- This project has not been compiled in an Unreal Engine installation in this environment. Treat it as a development package that needs local compilation and correction if your exact engine minor version differs.
- The project intentionally uses runtime procedural blockout geometry instead of claiming to contain a finished world asset.
- The `.uproject` targets UE 5.4. Update `IncludeOrderVersion` in Target.cs if using a different UE5 version.
