#include "request_handler.h"

const transport::Bus* RequestHandler::GetBus(const std::string_view bus_number) const {

    const transport::Bus* bus = catalogue_.SearchBus(bus_number);

    if (!bus) throw std::invalid_argument("bus not found");

    return bus;
}

const std::set<std::string> RequestHandler::GetBusesByStop(std::string_view stop_name) const {
    return catalogue_.SearchStop(stop_name)->buses_on_this_stop;
}

bool RequestHandler::IsBusNumber(const std::string_view bus_number) const {
    return catalogue_.SearchBus(bus_number);
}

bool RequestHandler::IsStopName(const std::string_view stop_name) const {
    return catalogue_.SearchStop(stop_name);
}

svg::Document RequestHandler::RenderMap() const {
    return renderer_.GetSVG(catalogue_.SortBuses());
}

void RequestHandler::ProcessRequests(const json::Node& stat_requests) const {
    json::Array result;
    for (auto& request : stat_requests.AsArray()) {
        const auto& request_map = request.AsDict();
        const auto& type = request_map.at("type").AsString();
        if (type == "Stop") result.push_back(PrintStop(request_map).AsDict());
        if (type == "Bus") result.push_back(PrintRoute(request_map).AsDict());
        if (type == "Map") result.push_back(PrintMap(request_map).AsDict());
    }

    json::Print(json::Document{ result }, std::cout);
}


const json::Node RequestHandler::PrintRoute(const json::Map& request_map) const {
    json::Map result;
    const std::string& route_number = request_map.at("name").AsString();
    result["request_id"] = request_map.at("id").AsInt();
    if (!this->IsBusNumber(route_number)) {
        result["error_message"] = json::Node{ static_cast<std::string>("not found") };
    }
    else {
        result["curvature"] = this->GetBus(route_number)->curvature;
        result["route_length"] = this->GetBus(route_number)->marshrut_length;
        result["stop_count"] = static_cast<int>(this->GetBus(route_number)->stops_count);
        result["unique_stop_count"] = static_cast<int>(this->GetBus(route_number)->unique_stops_count);
    }

    return json::Node{ result };
}


const json::Node RequestHandler::PrintStop(const json::Map& request_map) const {
    json::Map result;
    const std::string& stop_name = request_map.at("name").AsString();
    result["request_id"] = request_map.at("id").AsInt();
    if (!this->IsStopName(stop_name)) {
        result["error_message"] = json::Node{ static_cast<std::string>("not found") };
    }
    else {
        json::Array buses;
        for (auto& bus : this->GetBusesByStop(stop_name)) {
            buses.push_back(bus);
        }
        result["buses"] = buses;
    }

    return json::Node{ result };
}


const json::Node RequestHandler::PrintMap(const json::Map& request_map) const {
    json::Map result;
    result["request_id"] = request_map.at("id").AsInt();
    std::ostringstream strm;
    svg::Document map = this->RenderMap();
    map.Render(strm);
    result["map"] = strm.str();

    return json::Node{ result };
}
