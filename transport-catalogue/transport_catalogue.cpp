#include "transport_catalogue.h" 

namespace transport {

    void TransportCatalogue::AddStop(std::string_view stop_name, const geo::Coordinates crds) {
        bus_stops_.push_back({ std::string(stop_name), crds, {} });
        stopname_to_stop_[bus_stops_.back().stop_name] = &bus_stops_.back();
    }

    void TransportCatalogue::AddBus(std::string_view bus_name, const std::vector<const Stop*>& marshrut, bool crug) {

        Bus temp_bus;

        temp_bus.bus_name = bus_name;

        temp_bus.crug = crug;

        temp_bus.marshrut = marshrut;

        if (!crug)
        {
            temp_bus.stops_count = (marshrut.size() * 2) - 1;
        }
        else
        {
            temp_bus.stops_count = marshrut.size();
        }

        int marshrut_length = 0;
        double geo_length = 0.0;

        for (size_t i = 0; i < marshrut.size() - 1; ++i) {
            auto from = marshrut[i];
            auto to = marshrut[i + 1];
            if (crug) {
                marshrut_length += GetDistance(from, to);
                geo_length += geo::ComputeDistance(from->crds,
                    to->crds);
            }
            else {
                marshrut_length += GetDistance(from, to) + GetDistance(to, from);
                geo_length += geo::ComputeDistance(from->crds,
                    to->crds) * 2;
            }
        }

        std::unordered_set <const Stop*> set_of_unique_stops(marshrut.begin(), marshrut.end());
        temp_bus.unique_stops_count = set_of_unique_stops.size();

        temp_bus.marshrut_length = marshrut_length;
        temp_bus.curvature = marshrut_length / geo_length;

        buses_.push_back(temp_bus);

        busname_to_bus_[buses_.back().bus_name] = &buses_.back();
        for (const auto& route_stop : marshrut) {
            for (auto& stop_ : bus_stops_) {
                if (stop_.stop_name == route_stop->stop_name) stop_.buses_on_this_stop.insert(std::string(bus_name));
            }
        }
    }

    const Bus* TransportCatalogue::SearchBus(std::string_view bus_number) const {
        return busname_to_bus_.count(bus_number) ? busname_to_bus_.at(bus_number) : nullptr;
    }

    const Stop* TransportCatalogue::SearchStop(std::string_view stop_name) const {
        return stopname_to_stop_.count(stop_name) ? stopname_to_stop_.at(stop_name) : nullptr;
    }

    void TransportCatalogue::SetDistance(const Stop* from, const Stop* to, const int distance) {
        stop_distances_[{from, to}] = distance;
    }

    int TransportCatalogue::GetDistance(const Stop* from, const Stop* to) const {
        if (stop_distances_.count({ from, to })) return stop_distances_.at({ from, to });
        else if (stop_distances_.count({ to, from })) return stop_distances_.at({ to, from });
        else return 0;
    }

    const std::map<std::string_view, const Bus*> TransportCatalogue::SortBuses() const {

        std::map<std::string_view, const Bus*> result(busname_to_bus_.begin(), busname_to_bus_.end());

        return result;
    }

    const std::map<std::string_view, const Stop*> TransportCatalogue::SortStops() const {
        std::map<std::string_view, const Stop*> result;
        for (const auto& stop : stopname_to_stop_) {
            result.emplace(stop);
        }
        return result;
    }

} // namespace transport 
