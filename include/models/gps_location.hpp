/*--------------------------------------------------------------------
 *  Copyright (c) Spudmash Media Pty Ltd. All rights reserved.
 *  Licensed under the MIT License.
 *  See License.txt in the project root for license information.
 *------------------------------------------------------------------*/
#pragma once

#include <nlohmann/json.hpp>
#include <string>

namespace com_spudmash_cppuserapi::models
{

struct GpsLocation
{
    std::string latitude;
    std::string longitude;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(GpsLocation, latitude, longitude)
};

} // namespace com_spudmash_cppuserapi::models
