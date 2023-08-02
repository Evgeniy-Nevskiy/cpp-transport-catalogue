#pragma once

#include "transport_catalogue.h"

namespace transport {

	void ShowRequests(std::istream& in, TransportCatalogue& catalogue, std::ostream& out);
	void ShowBus(std::string& line, TransportCatalogue& catalogue, std::ostream& out);
	void ShowStop(std::string& line, TransportCatalogue& catalogue, std::ostream& out);

} // namespace transport
