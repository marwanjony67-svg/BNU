# BNU — BudgieOS Native Utilities

BNU is a small, cross-platform command-line toolkit for the BudgieOS project. It is written in C++17 and includes **BudgieOSMaker**, a generator for a minimal bare-metal kernel starter using Assembly, C, and C++.

> **Status:** early development. BNU is a user-space utility toolkit; BudgieOSMaker generates a separate experimental kernel project.

## BNU commands

| Command | Purpose |
|---|---|
| `bnu help` | Show available commands |
| `bnu sysinfo` | Show operating-system and architecture information |
| `bnu memory` | Show physical memory information where supported |
| `bnu files [PATH]` | List files in a directory |
| `bnu process` | Show this BNU process ID |
| `bnu update` | Explain the planned update workflow |

## BudgieOSMaker — generate an OS kernel starter

From the BNU repository root:

```sh
chmod +x tools/budgieosmaker
./tools/budgieosmaker BudgieOS-OS
cd BudgieOS-OS
make check-tools
make
make iso
```

The generator creates:
- `kernel/boot.S` — Multiboot2 assembly entry and stack
- `kernel/kernel.c` — freestanding C kernel entry and VGA text output
- `kernel/kernel.cpp` — C++ kernel initialization hook
- `linker.ld` — kernel linker layout
- `boot/grub/grub.cfg` — GRUB boot menu
- `Makefile` — cross-compile and ISO build targets

**Toolchain:** `i686-elf-gcc`, `i686-elf-g++`, GNU Make, GRUB utilities, and `xorriso`. The generated starter targets 32-bit x86 Multiboot2 and is intended for emulator testing. It is not a complete OS and does not yet provide drivers, storage, networking, or userspace.

## Build BNU itself

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

## License

MIT — see [LICENSE](LICENSE).
