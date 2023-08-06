#include "json_reader.h"
#include "request_handler.h"

int main() {
#ifdef __APPLE__
    freopen("input.json", "r", stdin);
    freopen("output.json", "w", stdout);
    //freopen("error-output.txt", "w", stderr);
#endif

    transport::TransportCatalogue tc;
    JsonReader json_file(std::cin);

    json_file.FillCatalogue(tc);

    const auto& stat_requests = json_file.GetStatRequests();
    const auto& render_settings = json_file.GetRenderSettings().AsDict();
    const auto& renderer = json_file.FillRenderSettings(render_settings);

    RequestHandler rh(tc, renderer);
    json_file.ProcessRequests(stat_requests, rh);
}
