/*--------------------------------------------------------------------
 *  Copyright (c) Spudmash Media Pty Ltd. All rights reserved.
 *  Licensed under the MIT License.
 *  See License.txt in the project root for license information.
 *------------------------------------------------------------------*/

#pragma once

#include "dtos/user_dto.hpp"
#include "dtos/user_response.hpp"
#include "models/user.hpp"
#include <format>
#include <string>

namespace com_spudmash_cppuserapi::dtos::mappers
{

class UserResponseMapper
{
  public:
    static dtos::UserResponse MapFromUserModel(const models::User &model)
    {
        dtos::UserResponse response;
        dtos::UserDto item;

        response.users.push_back(dtos::UserDto{
            MapName(model.name), MapLocation(model.location), model.email});
        return response;
    }

    static dtos::UserResponse
    MapFromUserModels(const std::vector<models::User> &models)
    {
        dtos::UserResponse response;

        for (auto &model : models)
        {
            response.users.push_back(dtos::UserDto{
                MapName(model.name), MapLocation(model.location), model.email});
        }

        return response;
    }

  private:
    static std::string MapName(const models::Name &src)
    {
        return std::format("{} {} {}", src.title, src.first, src.last);
    }

    static std::string MapLocation(const models::Location &src)
    {
        return std::format("{} {}, {} {} {}, {}", src.street.number,
                           src.street.name, src.city, src.state, src.postcode,
                           src.country);
    }
};

} // namespace com_spudmash_cppuserapi::dtos::mappers
