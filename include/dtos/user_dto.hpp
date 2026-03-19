/*--------------------------------------------------------------------
 *  Copyright (c) Spudmash Media Pty Ltd. All rights reserved.
 *  Licensed under the MIT License.
 *  See License.txt in the project root for license information.
 *------------------------------------------------------------------*/

#pragma once

#include <crow.h>
#include <nlohmann/json.hpp>
#include <string>

namespace com_spudmash_cppuserapi::dtos
{

class UserDto
{
  public:
    std::string name;
    std::string address;
    std::string email;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(UserDto, name, address, email)
};

} // namespace com_spudmash_cppuserapi::dtos
