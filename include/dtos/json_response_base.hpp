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

template <typename T> class JsonResponseBase : public crow::returnable
{
  protected:
    nlohmann::json error_;

  public:
    JsonResponseBase() : returnable("application/json")
    {
        error_ = {{"code", 200}, {"message", "Ok"}};
    };

    virtual ~JsonResponseBase() = default;

    virtual nlohmann::json to_json() const
    {
        return nlohmann::json{{}};
    }

    void set_error(const int &code = 200, const std::string &msg = "")
    {
        error_ = nlohmann::json({{"code", code}, {"message", msg}});
    }

    std::string dump() const override
    {
        return nlohmann::json{{"error", error_}, {"data", this->to_json()}}
            .dump();
    };
};

} // namespace com_spudmash_cppuserapi::dtos
