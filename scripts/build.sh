#!/usr/bin/env sh
set -eu

ROOT_DIR=$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)
BUILD_DIR="$ROOT_DIR/build"
CXX_BIN=${CXX:-c++}

mkdir -p "$BUILD_DIR"
"$CXX_BIN" -std=c++17 -O2 -Wall -Wextra -Wpedantic \
  -I"$ROOT_DIR/src" \
  "$ROOT_DIR/src/main.cpp" "$ROOT_DIR/src/system.cpp" \
  -o "$BUILD_DIR/bnu"

printf '\nBuild complete: %s\n' "$BUILD_DIR/bnu"
printf 'Try: %s help\n' "$BUILD_DIR/bnu"
