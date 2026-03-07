/*--------------------------------------------------------------------
 *  Copyright (c) Spudmash Media Pty Ltd. All rights reserved.
 *  Licensed under the MIT License.
 *  See License.txt in the project root for license information.
 *------------------------------------------------------------------*/

#pragma once

#include "crow.h"
#include "dtos/json_response_base.hpp"
#include "dtos/user_dto.hpp"
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

namespace com_spudmash_cppuserapi::dtos
{

class UserResponse : public JsonResponseBase<UserResponse>
{
  public:
    nlohmann::json to_json() const override
    {
        std::vector<nlohmann::json> user_json_array;
        std::transform(users.begin(), users.end(),
                       std::back_inserter(user_json_array),
                       [](const dtos::UserDto &user) { return user; });

        return nlohmann::json{{"users", user_json_array}};
    }

    std::vector<dtos::UserDto> users;
};

} // namespace com_spudmash_cppuserapi::dtos
