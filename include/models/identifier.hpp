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

struct Identifier
{
    std::string name;
    std::optional<std::string> value;

    friend void to_json(nlohmann::json &j, const Identifier &i)
    {
        j = nlohmann::json{{"name", i.name}};
        if (i.value)
            j["value"] = *i.value;
        else
            j["value"] = nullptr;
    }

    friend void from_json(const nlohmann::json &j, Identifier &i)
    {
        j.at("name").get_to(i.name);
        if (j.at("value").is_string())
        {
            i.value = j.at("value").get<std::string>();
        }
        else
        {
            i.value = std::nullopt;
        }
    }
};

} // namespace com_spudmash_cppuserapi::models
