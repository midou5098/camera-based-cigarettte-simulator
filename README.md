# Gesture-Controlled Cigarette Simulator

A desktop experiment that connects real-time hand tracking to an SDL2 animation. A Python MediaPipe/OpenCV process detects whether the user's hand is open or closed, writes that state to `state.txt`, and the C++ SDL application uses it to advance a cigarette burn animation.

## Features

- Webcam hand tracking with MediaPipe Hands.
- Open/closed hand classification from finger landmarks.
- Python-to-C++ communication through a lightweight shared text file.
- SDL2 menu for selecting a cigarette type.
- Animated flame sprite sheet.
- Progressive burn/ash reveal using SDL clipping rectangles.
- Manual keyboard fallback for advancing the burn.
- Multiple textured cigarette assets.

## Tech Stack

| Layer | Technology |
| --- | --- |
| Simulation | C++, SDL2, SDL2_image, SDL2_ttf, SDL2_gfx |
| Gesture detection | Python, OpenCV, MediaPipe |
| IPC | `state.txt` file polling |

## Project Structure

```text
.
|-- main.cpp          # SDL application entry point and render loop
|-- headers.h         # SDL wrapper, UI, texture loading, gesture state polling, animation logic
|-- app.py            # MediaPipe/OpenCV hand detector
|-- state.txt         # Runtime state bridge: 1=open, 0=closed
|-- assets/           # Cigarette textures, smoked overlays, flame sprite sheet
|-- font.ttf          # UI font
|-- font2.ttf         # UI font
|-- font.otf          # UI font
|-- venv311/          # Local Python environment artifact
`-- output/main       # Existing compiled binary artifact
```

## Gesture State

`app.py` writes one of two values to `state.txt`:

| Value | Meaning |
| --- | --- |
| `1` | Open hand detected. |
| `0` | Closed hand or no open-hand state detected. |

The SDL app reads this file during `uinter::update()`. When the cigarette is burning and the file contains `1`, the burn position advances over time.

## Install Python Dependencies

```bash
python3 -m venv venv311
source venv311/bin/activate
pip install opencv-python mediapipe
```

## Build C++ App

Install SDL dependencies on Ubuntu/Debian:

```bash
sudo apt install build-essential libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev libsdl2-gfx-dev
```

Compile from the repository root:

```bash
g++ main.cpp -o cigarette-simulator \
  -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_gfx -std=c++17
```

## Run

Start the gesture detector in one terminal:

```bash
python app.py
```

Start the SDL simulator in another terminal:

```bash
./cigarette-simulator
```

Run both from the repository root so `state.txt`, fonts, and assets resolve correctly.

## Controls

| Input | Action |
| --- | --- |
| Mouse click | Select a cigarette type. |
| `smoke !` button | Start the simulation. |
| Open hand | Advance the burn while the gesture detector is running. |
| `I` | Manual burn advance fallback. |
| `Esc` | Return to the selection menu. |

## How It Works

The visual effect is built from three layers:

1. The base cigarette texture.
2. A smoked/ash overlay texture.
3. An animated flame sprite sheet.

The variable `fy` controls both the flame position and the clipping rectangle used to reveal more of the smoked overlay. As the hand detector reports an open hand, `fy` increases, making the burn progress downward.

## Known Limitations

- File polling works for a prototype but is less robust than sockets, pipes, or shared memory.
- Webcam recognition depends on lighting and camera quality.
- The detector must be launched separately from the SDL app.
- Window size and UI positions are fixed.
