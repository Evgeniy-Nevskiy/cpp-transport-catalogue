#pragma once

#include "geo.h"

#include <string>
#include <unordered_map>
#include <vector>
#include <string_view>

namespace domain {

    struct Stop {
        Stop(const std::string& stop_name, const geo::Coordinates& crds);

        int GetDistance(Stop* to);

        std::string stop_name;
        geo::Coordinates crds;
        std::unordered_map<std::string_view, int> stop_distances_;
    };

    struct Bus {
        Bus(const std::string& bus_name, std::vector<Stop*> marshrut, bool crug);

        std::string bus_name;
        std::vector<Stop*> marshrut;
        bool crug;
        Stop* final_stop = nullptr;

    };

} //namespace domain