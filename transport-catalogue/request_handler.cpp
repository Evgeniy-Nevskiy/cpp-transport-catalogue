#include "request_handler.h"
#include <optional>


std::optional<transport::BusStat> RequestHandler::GetBusStat(const std::string_view bus_number) const
{
    return catalogue_.GetBusStat(bus_number);
}

const std::set<std::string> RequestHandler::GetBusesByStop(std::string_view stop_name) const {
    return catalogue_.FindStop(stop_name)->buses_on_this_stop;
}

bool RequestHandler::IsBusName(const std::string_view bus_number) const {
    return catalogue_.FindBus(bus_number);
}

bool RequestHandler::IsStopName(const std::string_view stop_name) const {
    return catalogue_.FindStop(stop_name);
}

svg::Document RequestHandler::RenderMap() const {
    return renderer_.GetSVG(catalogue_.GetSortedAllBuses());
}
