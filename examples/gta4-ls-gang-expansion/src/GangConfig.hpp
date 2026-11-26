#pragma once

#include <string>
#include <vector>

namespace lsmod {

struct Faction {
    std::string name;
    std::string color;
};

struct District {
    std::string name;
    std::string faction;
};

struct Config {
    std::vector<Faction> factions;
    std::vector<District> districts;
};

bool loadConfig(const std::string& path, Config& out, std::string& error);
bool validateConfig(const Config& config, std::string& error);
void printSummary(const Config& config);

} // namespace lsmod
