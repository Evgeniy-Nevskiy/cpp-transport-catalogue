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

const std::optional<graph::Router<double>::RouteInfo> RequestHandler::GetOptimalRoute(const std::string_view stop_from, const std::string_view stop_to) const {
    return router_.FindRoute(stop_from, stop_to);
}

const graph::DirectedWeightedGraph<double>& RequestHandler::GetRouterGraph() const {
    return router_.GetGraph();
}

svg::Document RequestHandler::RenderMap() const {
    return renderer_.GetSVG(catalogue_.SortBuses());
}
