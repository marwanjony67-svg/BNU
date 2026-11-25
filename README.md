# BNU — BudgieOS Native Utilities

BNU is a small, cross-platform command-line toolkit for the BudgieOS project. It is written in C++17 and is designed as a practical starter project for native system utilities.

> **Status:** early development. BNU is a user-space utility toolkit, not an operating-system kernel.

## Commands

| Command | Purpose |
|---|---|
| `bnu help` | Show available commands |
| `bnu sysinfo` | Show operating-system and architecture information |
| `bnu memory` | Show physical memory information where supported |
| `bnu files [PATH]` | List files in a directory |
| `bnu process` | Show this BNU process ID |
| `bnu update` | Explain the planned update workflow |

## Build

### Linux / macOS / compatible POSIX shell

```sh
chmod +x scripts/build.sh
./scripts/build.sh
./build/bnu help
```

### Windows (MSYS2 MinGW-w64 or another C++17 compiler)

```sh
g++ -std=c++17 -O2 -Wall -Wextra -pedantic -Isrc src/main.cpp src/system.cpp -o bnu.exe
bnu.exe help
```

### CMake

```sh
cmake -S . -B build-cmake
cmake --build build-cmake --config Release
```

## Project layout

- `src/` — application source
- `scripts/` — build helper scripts
- `CMakeLists.txt` — CMake build definition
- `Makefile` — Make build definition

## Safety and scope

BNU currently reports basic information and lists directories only. It does not modify system settings, terminate processes, install software, or perform privileged operations. The `update` command is informational and does not download or execute anything.

## License

MIT — see [LICENSE](LICENSE).
