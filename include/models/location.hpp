/*--------------------------------------------------------------------
 *  Copyright (c) Spudmash Media Pty Ltd. All rights reserved.
 *  Licensed under the MIT License.
 *  See License.txt in the project root for license information.
 *------------------------------------------------------------------*/

#pragma once

#include "models/gps_location.hpp"
#include "models/street.hpp"
#include "models/timezone.hpp"
#include <nlohmann/json.hpp>
#include <string>
#include <variant>

namespace com_spudmash_cppuserapi::models
{

struct Location
{
    Street street;
    std::string city;
    std::string state;
    std::string country;
    // std::variant<int, std::string> postcode;
    std::string postcode; // we're handling this
    GpsLocation coordinates;
    Timezone timezone;

    friend void to_json(nlohmann::json &j, const Location &l)
    {
        j = nlohmann::json{{"street", l.street},
                           {"city", l.city},
                           {"state", l.state},
                           {"country", l.country},
                           {"coordinates", l.coordinates},
                           {"timezone", l.timezone}};
    }

    friend void from_json(const nlohmann::json &j, Location &l)
    {
        j.at("street").get_to(l.street);
        j.at("city").get_to(l.city);
        j.at("state").get_to(l.state);
        j.at("country").get_to(l.country);
        j.at("coordinates").get_to(l.coordinates);
        j.at("timezone").get_to(l.timezone);

        const auto &p = j.at("postcode");
        if (p.is_number())
        {
            l.postcode =
                std::to_string(p.get<int>()); // we are parsing this to a string
        }
        else
        {
            l.postcode = p.get<std::string>();
        }
    }
};

} // namespace com_spudmash_cppuserapi::models
