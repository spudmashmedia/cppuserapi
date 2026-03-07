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

struct Login
{
    std::string uuid;
    std::string username;
    std::string password;
    std::string salt;
    std::string md5;
    std::string sha1;
    std::string sha256;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Login, uuid, username, password, salt, md5,
                                   sha1, sha256)
};

} // namespace com_spudmash_cppuserapi::models
