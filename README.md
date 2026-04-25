# OpeningTrainer_VectorPieces_Prototype

A disposable Qt/C++ prototype repository for experimenting with procedural/vector chess piece rendering.

> This is **not** the main Opening Trainer application repository.

## Purpose

This project validates a rendering pipeline for chess piece assets:
1. Define piece geometry procedurally (normalized vector space).
2. Rasterize into `QPixmap` at target square sizes and device pixel ratio.
3. Cache rendered pixmaps.
4. Reuse cached pixmaps in UI painting.

The first implementation includes only a placeholder **queen** (white + black variants) rendered using `QPainterPath`.

## Build Requirements

- CMake 3.16+
- C++17 compiler
- Qt 6 (Widgets)
- PowerShell (for helper scripts)

## Diagnostics

Run:

```powershell
.\diagnostic.ps1
```

The diagnostic script prints tool versions, Qt-related environment variables, key file checks, and build output checks.

## Build

Run:

```powershell
.\build_app.ps1
```

This script creates/uses a `build` folder, configures CMake, and builds the app.

## Run

Run:

```powershell
.\run.ps1
```

`run.ps1` checks for the built executable and, if missing, triggers a build first.

## Current Prototype Limitations

- Only one piece implemented (queen).
- No SVG/PNG export pipeline yet (folders are scaffolded only).
- No animation or advanced style controls.
- No integration with the main Opening Trainer codebase.
- UI is QWidget-based and intentionally minimal for iteration speed.
