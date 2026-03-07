/*--------------------------------------------------------------------
 *  Copyright (c) Spudmash Media Pty Ltd. All rights reserved.
 *  Licensed under the MIT License.
 *  See License.txt in the project root for license information.
 *------------------------------------------------------------------*/
#pragma once

#include "models/identifier.hpp"
#include "models/image_set.hpp"
#include "models/location.hpp"
#include "models/login.hpp"
#include "models/name.hpp"
#include "models/time_alive.hpp"
#include <nlohmann/json.hpp>
#include <string>

namespace com_spudmash_cppuserapi::models
{

struct User
{
    std::string gender;
    Name name;
    Location location;
    std::string email;
    Login login;
    TimeAlive dob;
    TimeAlive registered;
    std::string phone;
    std::string cell;
    Identifier id;
    ImageSet picture;
    std::string nat;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(User, gender, name, location, email, login,
                                   dob, registered, phone, cell, id, picture,
                                   nat)
};

} // namespace com_spudmash_cppuserapi::models
