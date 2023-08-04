#pragma once

#include "geo.h"
#include "domain.h"

#include <iostream>
#include <deque>
#include <string>
#include <unordered_map>
#include <vector>
#include <stdexcept>
#include <optional>
#include <unordered_set>
#include <set>
#include <map>

namespace transport {

    class TransportCatalogue {
    public:
        struct StopDistancesHasher {
            size_t operator()(const std::pair<const Stop*, const Stop*>& points) const {
                size_t hash_first = std::hash<const void*>{}(points.first);
                size_t hash_second = std::hash<const void*>{}(points.second);
                return hash_first + hash_second * 37;
            }
        };

        void AddStop(std::string_view stop_name, const geo::Coordinates coordinates);
        void AddBus(std::string_view bus_number, const std::vector<const Stop*>& marshrut, bool is_circle);

        const Bus* SearchBus(std::string_view bus_number) const;
        const Stop* SearchStop(std::string_view stop_name) const;

        void SetDistance(const Stop* from, const Stop* to, const int distance);
        int GetDistance(const Stop* from, const Stop* to) const;

        const std::map<std::string_view, const Bus*> SortBuses() const;

    private:
        std::deque<Stop> bus_stops_;
        std::deque<Bus> buses_;

        std::unordered_map<std::string_view, const Stop*> stopname_to_stop_;
        std::unordered_map<std::string_view, const Bus*> busname_to_bus_;

        std::unordered_map<std::pair<const Stop*, const Stop*>, int, StopDistancesHasher> stop_distances_;
    };

} // namespace transport
