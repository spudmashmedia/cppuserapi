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

struct Info
{
    std::string seed;
    int results;
    int page;
    std::string version;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Info, seed, results, page, version)
};

} // namespace com_spudmash_cppuserapi::models
