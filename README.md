# LVGL Hello World

A minimal "Hello World" project demonstrating LVGL running on Linux using SDL2 for display and input handling. This project serves as a clean starting point for LVGL applications on Linux systems.

The project demonstrates the basic structure needed to get LVGL running on Linux with hardware acceleration through SDL2.

## Prerequisites

### System dependencies
You need to install the following packages on your Linux system:

**Ubuntu/Debian:**
```bash
sudo apt update
sudo apt install build-essential cmake pkg-config libsdl2-dev libsdl2-image-dev
```

**Fedora/CentOS/RHEL:**
```bash
sudo dnf install gcc gcc-c++ cmake pkgconfig SDL2-devel SDL2_image-devel
```

**Arch Linux:**
```bash
sudo pacman -S base-devel cmake pkgconf sdl2 sdl2_image
```

### Development tools
- CMake 3.10 or higher
- GCC or Clang compiler
- Git (to clone LVGL submodule)

## Project structure

```
lvgl_hello_world/
├── CMakeLists.txt          # Main CMake configuration
├── src/
│   └── main.c             # Main application source
├── lvgl/                  # LVGL library (submodule)
├── build/                 # Build directory (created during build)
└── .vscode/               # VS Code workspace configuration
    └── workspace.json
```

## Clone and setup

```bash
# Clone the project recursively
git clone --recursive https://github.com/AndreCostaaa/lvgl_hello_world
cd lvgl_hello_world
```

## Building and Running

### Method 1: Command Line Interface (CLI)

#### Build

```bash
cmake -B build
cmake --build build -j$(nproc)
```

#### Run

```bash
./build/lvgl_hello_world
```

### Method 2: Using VS Code

#### Setup
1. Open VS Code in the project directory:

```bash
code lvgl.code-workspace
```

2. Install recommended extensions when prompted:
   - C/C++ Extension Pack
   - CMake Tools

3. Open the workspace file:
   - File > Open Workspace from File > `.vscode/workspace.json`

#### Build run and debug

- **Build:** Press `Ctrl+Shift+B` or use Command Palette (`Ctrl+Shift+P`) > "Tasks: Run Build Task"
- **Run:** Command Palette > "Tasks: Run Task" > "run"
- **Debug:** Press `F5` to build and start a debug session

