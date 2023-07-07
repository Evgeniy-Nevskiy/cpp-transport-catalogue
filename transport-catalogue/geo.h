#pragma once
#include <cmath>

namespace transport_catalogue
{
    namespace detail
    {
        namespace geo
        {

            const int EARTH_RADIUS = 6371000;
            const double PI = 3.1415926535;

            struct Coordinates
            {
                double lat;
                double lng;
                bool operator==(const Coordinates &other) const
                {
                    return lat == other.lat && lng == other.lng;
                }
            };

            inline double compute_distance(Coordinates start, Coordinates end)
            {
                using namespace std;
                if (!(start == end))
                {
                    const double dr = PI / 180.;
                    return acos(sin(start.lat * dr) * sin(end.lat * dr) + cos(start.lat * dr) * cos(end.lat * dr) * cos(abs(start.lng - end.lng) * dr)) * EARTH_RADIUS;
                }
                else
                {
                    return 0.0;
                }
            }

        }   // end namespace geo
    }       // end namespace detail
}           // end namespace transport_catalogue
