/*--------------------------------------------------------------------
 *  Copyright (c) Spudmash Media Pty Ltd. All rights reserved.
 *  Licensed under the MIT License.
 *  See License.txt in the project root for license information.
 *------------------------------------------------------------------*/
#pragma once

#include <nlohmann/json.hpp>
#include <string>

namespace com_spudmash_cppuserapi::dtos
{

struct HealthResponse
{
    std::string status;

    nlohmann::json serialize() const
    {
        return nlohmann::json{{"status", status}};
    }
};

} // namespace com_spudmash_cppuserapi::dtos
