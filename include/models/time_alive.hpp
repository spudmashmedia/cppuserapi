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

struct TimeAlive
{
    std::string date;
    int age;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(TimeAlive, date, age)
};

} // namespace com_spudmash_cppuserapi::models
