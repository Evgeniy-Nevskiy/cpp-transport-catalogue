#include "domain.h"
#include <stdexcept>

namespace domain {

    Stop::Stop(const std::string& stop_name, const geo::Coordinates& crds)
        : stop_name(stop_name)
        , crds(crds) {}

    int Stop::GetDistance(Stop* to) {
        if (stop_distances_.count(to->stop_name)) return stop_distances_.at(to->stop_name);
        else if (to->stop_distances_.count(this->stop_name)) return to->stop_distances_.at(this->stop_name);
        else return 0;
    }

    Bus::Bus(const std::string& bus_name, std::vector<Stop*> marshrut, bool crug)
        : bus_name(bus_name)
        , marshrut(marshrut)
        , crug(crug)
    {}

} //namespace domain