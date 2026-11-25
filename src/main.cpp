#include "system.hpp"

#include <exception>
#include <iostream>
#include <string>

namespace {
void print_help() {
    std::cout
        << "BNU — BudgieOS Native Utilities\n"
        << "Usage: bnu <command> [arguments]\n\n"
        << "Commands:\n"
        << "  help             Show this help message\n"
        << "  sysinfo          Show operating-system information\n"
        << "  linux            Show GNU/Linux distribution and tools\n"
        << "  memory           Show physical memory information\n"
        << "  files [PATH]     List a directory (default: current directory)\n"
        << "  process          Show the current BNU process ID\n"
        << "  update           Show update status and planned workflow\n";
}
}

int main(int argc, char* argv[]) {
    try {
        if (argc < 2 || std::string(argv[1]) == "help" ||
            std::string(argv[1]) == "--help" || std::string(argv[1]) == "-h") {
            print_help();
            return 0;
        }

        const std::string command = argv[1];
        if (command == "linux") {
            bnu::show_linux_info();
        } else if (command == "sysinfo") {
            bnu::show_sysinfo();
        } else if (command == "memory") {
            bnu::show_memory();
        } else if (command == "files") {
            bnu::list_files(argc >= 3 ? argv[2] : ".");
        } else if (command == "process") {
            bnu::show_process();
        } else if (command == "update") {
            bnu::show_update_status();
        } else {
            std::cerr << "bnu: unknown command: " << command << "\n";
            std::cerr << "Run 'bnu help' to see available commands.\n";
            return 2;
        }
    } catch (const std::exception& error) {
        std::cerr << "bnu: " << error.what() << "\n";
        return 1;
    }
    return 0;
}
