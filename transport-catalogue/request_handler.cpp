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

////////////////////////////////////////////////////////////////////////////

void RequestHandler::ProcessRequests(const json::Node& stat_requests, RequestHandler& rh) const {
    json::Array result;
    for (auto& request : stat_requests.AsArray()) {
        const auto& request_map = request.AsMap();
        const auto& type = request_map.at("type").AsString();
        if (type == "Stop") result.push_back(PrintStop(request_map, rh).AsMap());
        if (type == "Bus") result.push_back(PrintRoute(request_map, rh).AsMap());
        if (type == "Map") result.push_back(PrintMap(request_map, rh).AsMap());
    }

    json::Print(json::Document{ result }, std::cout);
}



///////////////////////////////////////////////////////////////////////////////

const json::Node RequestHandler::PrintRoute(const json::Dict& request_map, RequestHandler& rh) const {
    json::Dict result;
    const std::string& route_number = request_map.at("name").AsString();
    result["request_id"] = request_map.at("id").AsInt();
    if (!rh.IsBusNumber(route_number)) {
        result["error_message"] = json::Node{ static_cast<std::string>("not found") };
    }
    else {
        result["curvature"] = rh.GetBus(route_number)->curvature;
        result["route_length"] = rh.GetBus(route_number)->marshrut_length;
        result["stop_count"] = static_cast<int>(rh.GetBus(route_number)->stops_count);
        result["unique_stop_count"] = static_cast<int>(rh.GetBus(route_number)->unique_stops_count);
    }

    return json::Node{ result };
}


const json::Node RequestHandler::PrintStop(const json::Dict& request_map, RequestHandler& rh) const {
    json::Dict result;
    const std::string& stop_name = request_map.at("name").AsString();
    result["request_id"] = request_map.at("id").AsInt();
    if (!rh.IsStopName(stop_name)) {
        result["error_message"] = json::Node{ static_cast<std::string>("not found") };
    }
    else {
        json::Array buses;
        for (auto& bus : rh.GetBusesByStop(stop_name)) {
            buses.push_back(bus);
        }
        result["buses"] = buses;
    }

    return json::Node{ result };
}


const json::Node RequestHandler::PrintMap(const json::Dict& request_map, RequestHandler& rh) const {
    json::Dict result;
    result["request_id"] = request_map.at("id").AsInt();
    std::ostringstream strm;
    svg::Document map = rh.RenderMap();
    map.Render(strm);
    result["map"] = strm.str();

    return json::Node{ result };
}
