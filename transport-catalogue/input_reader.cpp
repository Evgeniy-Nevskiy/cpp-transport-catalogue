#include "input_reader.h"

namespace transport {

    void Parsing(std::istream& in, TransportCatalogue& catalogue) {
        std::vector<std::string> buses;
        std::vector<std::string> stops;
        std::vector<std::string> distances;
        size_t size;

        in >> size;
        for (size_t i = 0; i < size; ++i) {
            std::string word, str;
            in >> word;
            std::getline(in, str);
            if (word == "Stop") {
                stops.push_back(str);
            }
            if (word == "Bus") {
                buses.push_back(str);
            }
        }
        distances = stops;
        for (auto& stop : stops) {
            auto [stop_name, crds] = ParsingStop(stop);
            catalogue.AddStop(stop_name, crds);
        }
        for (auto& stop : distances) {
            AddDistances(stop, catalogue);
        }
        for (auto& bus : buses) {
            auto [bus_name, marshrut, crug] = ParsingBus(bus, catalogue);
            catalogue.AddBus(bus_name, marshrut, crug);
            bus = {};
        }
    }

    std::pair<std::string, geo::Coordinates> ParsingStop(std::string& str) {
        std::string stop_name = str.substr(1, str.find_first_of(':') - str.find_first_of(' ') - 1);
        double latitude = std::stod(str.substr(str.find_first_of(':') + 2, str.find_first_of(',') - 1));
        double longitude;
        str.erase(0, str.find_first_of(',') + 2);
        if (str.find_last_of(',') == str.npos) {
            longitude = std::stod(str.substr(0, str.npos - 1));
            str.clear();
        }
        else {
            longitude = std::stod(str.substr(0, str.find_first_of(',')));
            str.erase(0, str.find_first_of(',') + 2);
        }
        geo::Coordinates stop_coordinates = { latitude, longitude };

        return { stop_name, stop_coordinates };
    }

    void AddDistances(std::string& str, TransportCatalogue& catalogue) {
        if (!str.empty()) {
            std::string stopname_begin = ParsingStop(str).first;
            const Stop* first = catalogue.SearchStop(stopname_begin);

            while (!str.empty()) {
                int lenght = 0;
                std::string stopname_end;
                lenght = std::stoi(str.substr(0, str.find_first_of("m to ")));
                str.erase(0, str.find_first_of("m to ") + 5);
                if (str.find("m to ") == str.npos) {
                    stopname_end = str.substr(0, str.npos - 1);
                    const Stop* second = catalogue.SearchStop(stopname_end);
                    catalogue.SetDistance(first, second, lenght);
                    if (!catalogue.GetDistance(first, second)) {
                        catalogue.SetDistance(second, first, lenght);
                    }
                    str.clear();
                }
                else {
                    stopname_end = str.substr(0, str.find_first_of(','));
                    const Stop* second = catalogue.SearchStop(stopname_end);
                    catalogue.SetDistance(first, second, lenght);
                    if (!catalogue.GetDistance(first, second)) {
                        catalogue.SetDistance(second, first, lenght);
                    }
                    str.erase(0, str.find_first_of(',') + 2);
                }
            }
        }
    }

    std::tuple<std::string, std::vector<const Stop*>, bool> ParsingBus(std::string& str, transport::TransportCatalogue& catalogue) {
        std::vector<const Stop*> marshrut_stops;
        std::string bus_name = str.substr(1, str.find_first_of(':') - 1);
        str.erase(0, str.find_first_of(':') + 2);
        bool crug = false;
        std::string stop_name;
        auto pos = str.find('>') != str.npos ? '>' : '-';
        while (str.find(pos) != str.npos) {
            stop_name = str.substr(0, str.find_first_of(pos) - 1);
            const Stop* pointer_stop = catalogue.SearchStop(stop_name);
            marshrut_stops.push_back(pointer_stop);
            str.erase(0, str.find_first_of(pos) + 2);
        }
        stop_name = str.substr(0, str.npos - 1);
        const Stop* pointer_stop = catalogue.SearchStop(stop_name);
        marshrut_stops.push_back(pointer_stop);
        if (pos == '>') crug = true;

        return { bus_name, marshrut_stops, crug };
    }

} // namespace transport
