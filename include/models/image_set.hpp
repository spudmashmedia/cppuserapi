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

struct ImageSet
{
    std::string large;
    std::string medium;
    std::string thumbnail;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(ImageSet, large, medium, thumbnail)
};

} // namespace com_spudmash_cppuserapi::models
