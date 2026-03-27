/*--------------------------------------------------------------------
 *  Copyright (c) Spudmash Media Pty Ltd. All rights reserved.
 *  Licensed under the MIT License.
 *  See License.txt in the project root for license information.
 *------------------------------------------------------------------*/
#pragma once

#include "utils/config/api_options.h"
#include "utils/config/config_options.h"
#include "utils/config/user_service_options.h"

#include <filesystem>
#include <iostream>
#include <string>
#include <toml++/toml.hpp>

namespace com_spudmash_cppuserapi::utils::config
{

class Config
{
  public:
    static ConfigResponse
    read_config(const std::string &path = Config::default_filename)
    {
        ConfigResponse config;

        if (!std::filesystem::exists(path))
        {
            std::clog << "[config] file: " << path << " not found.\n";
        }

        toml::parse_result raw_config;

        try
        {
            raw_config = toml::parse_file(path);
        }
        catch (toml::parse_error &err)
        {
            std::clog << "[config] file: " << path
                      << " - exception: " << err.what() << "\n";
        }

        // Parse TOML Sections
        //
        if (auto server = raw_config["server"].as_table())
        {
            config.api.port = (*server)["port"].value_or(config.api.port);
            config.api.concurrency =
                (*server)["concurrency"].value_or(config.api.concurrency);
        }

        if (auto services = raw_config["services"].as_table())
        {
            config.userService.randomuser_limit = (*services)["randomuser_limit"].value_or(
                config.userService.randomuser_limit);

            config.userService.randomuser_host =
                (*services)["randomuser_host"].value_or(config.userService.randomuser_host);

            config.userService.randomuser_port =
                (*services)["randomuser_port"].value_or(config.userService.randomuser_port);

            config.userService.randomuser_path_api =
                (*services)["randomuser_path_api"].value_or(
                    config.userService.randomuser_path_api);
        }

        return config;
    }

  private:
    static constexpr char default_filename[]{"cppuserapi_config.toml"};
};

} // namespace com_spudmash_cppuserapi::utils::config
