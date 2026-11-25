#include "system.hpp"

#include <filesystem>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <system_error>

#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#else
#include <sys/types.h>
#include <unistd.h>
#if defined(__linux__)
#include <sys/sysinfo.h>
#endif
#endif

namespace bnu {
namespace {
const char* platform_name() {
#ifdef _WIN32
    return "Windows";
#elif defined(__APPLE__)
    return "macOS";
#elif defined(__linux__)
    return "Linux";
#else
    return "Unknown / unsupported platform";
#endif
}

const char* architecture_name() {
#if defined(__x86_64__) || defined(_M_X64)
    return "x86_64";
#elif defined(__aarch64__) || defined(_M_ARM64)
    return "ARM64";
#elif defined(__i386__) || defined(_M_IX86)
    return "x86";
#else
    return "Unknown";
#endif
}
}

void show_sysinfo() {
    std::cout << "BudgieOS Native Utilities (BNU)\n"
              << "Platform: " << platform_name() << "\n"
              << "Architecture: " << architecture_name() << "\n"
              << "C++ standard: C++17\n";
}

void show_memory() {
#ifdef _WIN32
    MEMORYSTATUSEX status{};
    status.dwLength = sizeof(status);
    if (!GlobalMemoryStatusEx(&status)) {
        throw std::runtime_error("could not read memory status");
    }
    const double total = static_cast<double>(status.ullTotalPhys) / (1024.0 * 1024.0);
    const double available = static_cast<double>(status.ullAvailPhys) / (1024.0 * 1024.0);
    std::cout << std::fixed << std::setprecision(1)
              << "Physical memory total: " << total << " MiB\n"
              << "Physical memory available: " << available << " MiB\n";
#elif defined(__linux__)
    struct sysinfo info {};
    if (sysinfo(&info) != 0) {
        throw std::runtime_error("could not read memory status");
    }
    const double unit = static_cast<double>(info.mem_unit);
    const double total = static_cast<double>(info.totalram) * unit / (1024.0 * 1024.0);
    const double available = static_cast<double>(info.freeram) * unit / (1024.0 * 1024.0);
    std::cout << std::fixed << std::setprecision(1)
              << "Physical memory total: " << total << " MiB\n"
              << "Free memory: " << available << " MiB\n";
#else
    std::cout << "Memory reporting is not implemented for this platform yet.\n";
#endif
}

void list_files(const std::string& path) {
    std::error_code error;
    const std::filesystem::path directory(path);
    if (!std::filesystem::exists(directory, error) || error) {
        throw std::runtime_error("path does not exist: " + path);
    }
    if (!std::filesystem::is_directory(directory, error) || error) {
        throw std::runtime_error("path is not a directory: " + path);
    }

    for (std::filesystem::directory_iterator it(directory, error), end;
         !error && it != end; it.increment(error)) {
        const auto name = it->path().filename().string();
        std::cout << (it->is_directory(error) ? "[DIR]  " : "[FILE] ") << name << "\n";
        if (error) break;
    }
    if (error) {
        throw std::runtime_error("could not read directory: " + error.message());
    }
}

void show_process() {
#ifdef _WIN32
    std::cout << "BNU process ID: " << GetCurrentProcessId() << "\n";
#else
    std::cout << "BNU process ID: " << static_cast<long long>(getpid()) << "\n";
#endif
}

void show_update_status() {
    std::cout << "BNU update service: not configured yet.\n"
              << "No files were downloaded or changed.\n"
              << "Future versions may check signed releases from the official BNU repository.\n";
}
}
