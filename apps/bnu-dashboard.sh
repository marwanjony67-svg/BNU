#!/usr/bin/env bash
# BNU Dashboard — a read-only Bash app for BudgieOS Native Utilities.
set -Eeuo pipefail

APP_NAME="BNU Dashboard"
VERSION="1.1.0"

pause() {
  printf '\nPress Enter to return to the menu...'
  IFS= read -r _
}

show_header() {
  clear 2>/dev/null || true
  printf '====================================\n'
  printf '  %s v%s\n' "$APP_NAME" "$VERSION"
  printf '  BudgieOS Native Utilities\n'
  printf '====================================\n\n'
}

show_system() {
  printf 'System information\n'
  printf '%s\n' '------------------'
  printf 'OS: %s\n' "${OSTYPE:-unknown}"
  if [[ -r /etc/os-release ]]; then
    . /etc/os-release
    printf 'Distribution: %s\n' "${PRETTY_NAME:-unknown}"
    printf 'Environment: GNU/Linux\n'
  fi
  printf 'Kernel: '
  if command -v uname >/dev/null 2>&1; then uname -srmo; else printf 'uname unavailable\n'; fi
  printf 'User: %s\n' "${USER:-unknown}"
  printf 'Shell: %s\n' "${BASH_VERSION:-unknown}"
}

show_memory() {
  printf 'Memory information\n'
  printf '%s\n' '------------------'
  if [[ -r /proc/meminfo ]]; then
    grep -E '^(MemTotal|MemFree|MemAvailable|SwapTotal|SwapFree):' /proc/meminfo
  elif command -v vm_stat >/dev/null 2>&1; then
    vm_stat
  elif command -v free >/dev/null 2>&1; then
    free -h
  else
    printf 'Memory details are not available on this system.\n'
  fi
}

show_files() {
  local target="${1:-.}"
  printf 'Files in: %s\n' "$target"
  printf '%s\n' '------------------'
  if [[ -d "$target" ]]; then
    ls -la -- "$target"
  else
    printf 'Not a directory: %s\n' "$target"
    return 1
  fi
}

show_process() {
  printf 'BNU Dashboard process\n'
  printf '%s\n' '---------------------'
  printf 'PID: %s\n' "$$"
  printf 'Parent PID: %s\n' "$PPID"
}

while true; do
  show_header
  cat <<'MENU'
1) System information
2) Memory information
3) List files
4) Show app process
5) About BNU
0) Exit

MENU
  printf 'Select an option: '
  IFS= read -r choice || exit 0
  printf '\n'

  case "$choice" in
    1) show_system; pause ;;
    2) show_memory; pause ;;
    3)
      printf 'Directory path [.] : '
      IFS= read -r path
      show_files "${path:-.}" || true
      pause
      ;;
    4) show_process; pause ;;
    5)
      printf '%s\n' 'BNU Dashboard is a small, read-only Bash terminal app.'
      printf '%s\n' 'It does not change system settings or delete files.'
      pause
      ;;
    0) printf 'Goodbye from BNU.\n'; exit 0 ;;
    *) printf 'Unknown option.\n'; pause ;;
  esac
done
