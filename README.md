# C++ Code Editor

A lightweight custom code editor built with C++ and Qt 6.

The editor currently supports opening files and folders, navigating through a folder tree, editing files, and saving changes.

## Tech Stack

[![C++](https://img.shields.io/badge/C%2B%2B-00599C?style=flat-square&logo=cplusplus&logoColor=white)](https://isocpp.org/)
[![Qt](https://img.shields.io/badge/Qt_6-41CD52?style=flat-square&logo=qt&logoColor=white)](https://www.qt.io/)
[![CMake](https://img.shields.io/badge/CMake-064F8C?style=flat-square&logo=cmake&logoColor=white)](https://cmake.org/)

## Features

- Open files
- Open folders
- Folder and file tree
- Edit files
- Save files
- Save As

## Current Status

The editor is currently in early development.

| Feature | Status |
|---|---|
| Open File | Done |
| Open Folder | Done |
| Folder Tree | Done |
| Edit Files | Done |
| Save | Done |
| Save As | Done |
| Syntax Highlighting | Planned |
| Tabs | Planned |
| Find & Replace | Planned |
| Auto Completion | Planned |
| Terminal | Planned |
| Build & Run | Planned |
| Debugger | Planned |

## Requirements

- C++ compiler with C++26 support
- Qt 6
- CMake

## Building

### Clone

```bash
git clone <your-repository-url>
cd <your-project-folder>
```

### Build a Debian package

Install CMake, Ninja, a C++26-capable compiler, Qt 6 development libraries
(`qt6-base-dev` and `qt6-svg-dev` on Debian/Ubuntu), and `dpkg-dev`. Then run:

```bash
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Release
cmake --build build
cd build
cpack -G DEB
```

The `.deb` package will be created in `build/`. Install it with
`sudo apt install ./strata-*.deb`.
