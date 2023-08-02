#pragma once

#include "transport_catalogue.h"

#include <iostream>

namespace transport {

	void Parsing(std::istream& in, TransportCatalogue& catalogue);
	std::pair<std::string, geo::Coordinates> ParsingStop(std::string& line);
	void AddDistances(std::string& line, TransportCatalogue& catalogue);
	std::tuple<std::string, std::vector<const Stop*>, bool> ParsingBus(std::string& line, transport::TransportCatalogue& catalogue);

} // namespace transport
