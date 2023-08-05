#include "json_reader.h"
#include "request_handler.h"

int main() {
    transport::TransportCatalogue transport_catalogue;
    JsonReader file_json(std::cin);

    file_json.FillCatalogue(transport_catalogue);

    const auto& stat_requests = file_json.GetStatRequests();
    const auto& render_settings = file_json.GetRenderSettings().AsMap();
    const auto& renderer = file_json.FillRenderSettings(render_settings);




    RequestHandler rh(transport_catalogue, renderer);
    //file_json.ProcessRequests(stat_requests, rh);
    rh.ProcessRequests(stat_requests, rh);
}
