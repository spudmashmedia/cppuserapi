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

struct Name
{
    std::string title;
    std::string first;
    std::string last;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Name, title, first, last)
};

} // namespace com_spudmash_cppuserapi::models
