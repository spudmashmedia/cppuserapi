/*--------------------------------------------------------------------
 *  Copyright (c) Spudmash Media Pty Ltd. All rights reserved.
 *  Licensed under the MIT License.
 *  See License.txt in the project root for license information.
 *------------------------------------------------------------------*/

#pragma once

#include "crow.h"
#include <nlohmann/json.hpp>
#include <string>

namespace com_spudmash_cppuserapi::dtos
{

template <typename T> class JsonResponseBase : public crow::returnable
{
  public:
    JsonResponseBase() : returnable("application/json") {};

    virtual ~JsonResponseBase() = default;

    virtual nlohmann::json to_json() const
    {
        return nlohmann::json{{}};
    }

    std::string dump() const override
    {
        return nlohmann::json{{"data", this->to_json()}}.dump();
    };
};

} // namespace com_spudmash_cppuserapi::dtos
