#include "json_reader.h"
#include "request_handler.h"

int main() {
    transport::TransportCatalogue tc;
    JsonReader json_file(std::cin);

    json_file.FillCatalogue(tc);

    const auto& stat_requests = json_file.GetStatRequests();
    const auto& render_settings = json_file.GetRenderSettings();
    const auto& renderer = json_file.FillRenderSettings(render_settings);
    const auto& routing_settings = json_file.FillRoutingSettings(json_file.GetRoutingSettings());

    const transport::Router router = { routing_settings, tc };

    RequestHandler rh(tc, renderer, router);
    json_file.ProcessRequests(stat_requests, rh);
}