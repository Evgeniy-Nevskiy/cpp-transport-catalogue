#include "stat_reader.h"

#include <iomanip>

namespace transport {

    void ShowRequests(std::istream& in, TransportCatalogue& catalogue, std::ostream& out) {
        size_t requests_num;
        in >> requests_num;
        for (size_t i = 0; i < requests_num; ++i) {
            std::string keyword, str;
            in >> keyword;
            std::getline(in, str);
            if (keyword == "Bus") {
                ShowBus(str, catalogue, out);
            }
            if (keyword == "Stop") {
                ShowStop(str, catalogue, out);
            }
        }
    }

    void ShowBus(std::string& line, TransportCatalogue& catalogue, std::ostream& out) {
        std::string bus_name = line.substr(1, line.npos);

        auto it = catalogue.SearchBus(bus_name);
        if (it != nullptr)
        {
            out << "Bus " << it->bus_name << ": " << it->stops_count
                << " stops on route, " << it->unique_stops_count << " unique stops, " << it->marshrut_length
                << " route length, " << it->curvature << " curvature" << std::endl;
        }
     
        else
        {
            out << "Bus " << bus_name << ": not found" << std::endl;
        }
       
    }

    void ShowStop(std::string& line, TransportCatalogue& catalogue, std::ostream& out) {
        std::string stop_name = line.substr(1, line.npos);
        if (catalogue.SearchStop(stop_name)) {
            out << "Stop " << stop_name << ": ";
            auto buses = catalogue.GetBusesByStop(stop_name);
            if (!buses.empty()) {
                out << "buses ";
                for (const auto& bus : buses) {
                    out << bus << " ";
                }
                out << "\n";
            }
            else {
                out << "no buses\n";
            }
        }
        else {
            out << "Stop " << stop_name << ": not found\n";
        }
    }

} // namespace transport
