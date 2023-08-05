#pragma once

#include "json.h"
#include "transport_catalogue.h"
#include "map_renderer.h"

#include <sstream>

class RequestHandler {
public:
    RequestHandler(const transport::TransportCatalogue& catalogue, const renderer::MapRenderer& renderer)
        : catalogue_(catalogue)
        , renderer_(renderer)
    {
    }
    ////////////////////////////////////////////////////////
    void ProcessRequests(const json::Node& stat_requests, RequestHandler& rh) const;
    const json::Node PrintRoute(const json::Dict& request_map, RequestHandler& rh) const;
    const json::Node PrintStop(const json::Dict& request_map, RequestHandler& rh) const;
    const json::Node PrintMap(const json::Dict& request_map, RequestHandler& rh) const;
    ///////////////////////////////////////////////////////


    const transport::Bus* GetBus(const std::string_view bus_number) const;

    const std::set<std::string> GetBusesByStop(std::string_view stop_name) const;

    bool IsBusNumber(const std::string_view bus_number) const;
    bool IsStopName(const std::string_view stop_name) const;

    svg::Document RenderMap() const;

private:
    const transport::TransportCatalogue& catalogue_;
    const renderer::MapRenderer& renderer_;
};
