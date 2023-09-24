#include "transport_catalogue.h"

#include <string>
#include <vector>
#include <algorithm>

namespace transport {

    using namespace std::literals;

    void Catalogue::AddStop(const std::string& name, const geo::Coordinates& crds) {
        bus_stops_.push_back(Stop(name, crds));
        Stop* added_stop = &bus_stops_.back();
        stop_to_buses_[added_stop->stop_name];
        stopname_to_stop_[added_stop->stop_name] = added_stop;
    }

    void Catalogue::AddBus(const std::string& name, const std::vector<Stop*>& marshrut, bool crug) {
        buses_.push_back(Bus(name, marshrut, crug));
        Bus* added_bus = &buses_.back();
        for (const Stop* s : marshrut) {
            stop_to_buses_[s->stop_name][added_bus->bus_name] = added_bus;
        }
        busname_to_bus_[added_bus->bus_name] = added_bus;
    }

   Stop* Catalogue::SearchStop(const std::string_view stop) {
        return stopname_to_stop_.count(stop) ? stopname_to_stop_.at(stop) : nullptr;
    }

   const Stop* Catalogue::SearchStop(const std::string_view stop) const {
        return stopname_to_stop_.count(stop) ? stopname_to_stop_.at(stop) : nullptr;
    }

    Bus* Catalogue::SearchBus(const std::string_view bus_name) {
        return busname_to_bus_.count(bus_name) ? busname_to_bus_.at(bus_name) : nullptr;
    }

    const Bus* Catalogue::SearchBus(const std::string_view bus_name) const {
        return busname_to_bus_.count(bus_name) ? busname_to_bus_.at(bus_name) : nullptr;
    }

    std::map<std::string_view, Bus*> Catalogue::GetBusesOnStop(const std::string_view stop_name) {
        return stop_to_buses_.at(stop_name);
    }

    const std::map<std::string_view, Bus*> Catalogue::GetBusesOnStop(const std::string_view stop_name) const {
        return stop_to_buses_.at(stop_name);
    }

    void Catalogue::SetDistance(Stop* from, Stop* to, int dist) {
        from->stop_distances_[to->stop_name] = dist;
    }

    const std::map<std::string_view, Bus*>& Catalogue::GetSortedAllBuses() const {
        return busname_to_bus_;
    }

    const std::map<std::string_view, Stop*>& Catalogue::GetSortedAllStops() const {
        return stopname_to_stop_;
    }

} // namespace transport