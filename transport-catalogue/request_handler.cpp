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
