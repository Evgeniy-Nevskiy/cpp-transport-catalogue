#pragma once

#include "geo.h"

#include <iostream>
#include <deque>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <stdexcept>
#include <unordered_set>
#include <set>

namespace transport {

    struct Stop {
        std::string stop_name;
        geo::Coordinates crds;
        std::set<std::string> buses_on_this_stop;
    };

    struct Bus {
        std::string bus_name;
        std::vector<const Stop*> marshrut;
        bool crug;

        size_t stops_count;
        size_t unique_stops_count;
        double marshrut_length;
        double curvature;
    };

    class TransportCatalogue {
    public:
        struct StopDistancesHasher {
            size_t operator()(const std::pair<const Stop*, const Stop*>& points) const {
                size_t hash_first = std::hash<const void*>{}(points.first);
                size_t hash_second = std::hash<const void*>{}(points.second);
                return hash_first + hash_second * 37;
            }
        };

        void AddStop(std::string_view stop_name, const geo::Coordinates crds);
        void AddBus(std::string_view bus_name, const std::vector<const Stop*> marshrut, bool crug);

        const std::set<std::string> GetBusesByStop(std::string_view stop_name) const;

        const Bus* SearchBus(std::string_view bus_name) const;
        const Stop* SearchStop(std::string_view stop_name) const;

        void SetDistance(const Stop* from, const Stop* to, const int distance);
        int GetDistance(const Stop* from, const Stop* to) const;

    private:
        std::deque<Stop> bus_stops_;
        std::deque<Bus> buses_;

        std::unordered_map<std::string_view, const Stop*> stopname_to_stop_;
        std::unordered_map<std::string_view, const Bus*> busname_to_bus_;

        std::unordered_map<std::pair<const Stop*, const Stop*>, int, StopDistancesHasher> stop_distances_;
    };

} // namespace transport
