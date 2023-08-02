#include "input_reader.h"
#include "stat_reader.h"

using namespace transport;

int main() {
    TransportCatalogue transport_catalogue;
    Parsing(std::cin, transport_catalogue);
    ShowRequests(std::cin, transport_catalogue, std::cout);
}
