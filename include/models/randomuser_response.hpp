/*--------------------------------------------------------------------
 *  Copyright (c) Spudmash Media Pty Ltd. All rights reserved.
 *  Licensed under the MIT License.
 *  See License.txt in the project root for license information.
 *------------------------------------------------------------------*/
#pragma once

#include "models/user.hpp"
#include "models/info.hpp"
#include <nlohmann/json.hpp>
#include <vector>

namespace com_spudmash_cppuserapi::models
{

struct RandomUserResponse
{
    std::vector<User> results;
    Info info;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(RandomUserResponse, results, info)
};

} // namespace com_spudmash_cppuserapi::models
