#pragma once

#include "geo.h"
#include "domain.h"

#include <deque>
#include <vector>
#include <string>
#include <unordered_map>
#include <string_view>
#include <map>

namespace transport {

    using namespace domain;

    class Catalogue {
    public:

        void AddStop(const std::string& name, const geo::Coordinates& crds);

        void AddBus(const std::string& num, const std::vector<Stop*>& marshrut, bool crug);

       Stop* SearchStop(const std::string_view stop);

        const Stop* SearchStop(const std::string_view stop) const;

        Bus* SearchBus(const std::string_view bus_num);

        const Bus* SearchBus(const std::string_view bus_num) const;

        std::map<std::string_view, Bus*> GetBusesOnStop(const std::string_view stop_name);

        const std::map<std::string_view, Bus*> GetBusesOnStop(const std::string_view stop_name) const;

        void SetDistance(Stop* from, Stop* to, int dist);

        const std::map <std::string_view, Bus*>& GetSortedAllBuses() const;

        const std::map <std::string_view, Stop*>& GetSortedAllStops() const;

    private:

        std::deque<Stop> bus_stops_;
        std::deque<Bus> buses_;
    
        std::map < std::string_view, Stop* > stopname_to_stop_;
        std::map < std::string_view, Bus* > busname_to_bus_;

        std::unordered_map < std::string_view, std::map<std::string_view, Bus*>> stop_to_buses_;
    };
    
} // namespace transport