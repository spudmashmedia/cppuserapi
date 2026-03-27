/*--------------------------------------------------------------------
 *  Copyright (c) Spudmash Media Pty Ltd. All rights reserved.
 *  Licensed under the MIT License.
 *  See License.txt in the project root for license information.
 *------------------------------------------------------------------*/
#include "api/api.h"
#include "controllers/catch_all_controller.h"
#include "controllers/health_controller.h"
#include "controllers/user_controller.h"
#include "services/user_service.h"
#include "utils/config/config.hpp"
#include "utils/config/config_options.h"
#include "utils/http/boost_http_client.h"

#include <stdexcept>

using namespace com_spudmash_cppuserapi::api;
using namespace com_spudmash_cppuserapi::utils::config;
using namespace com_spudmash_cppuserapi::utils::http;
using namespace com_spudmash_cppuserapi::services;
using namespace com_spudmash_cppuserapi::controllers;

int main()
{
    // Bootstrap dependencies - Singletons use shared pointers
    auto cfg =
        std::make_shared<ConfigResponse>(Config::read_config());
    auto client =
        std::make_shared<BoostHttpClient>(cfg->userService.randomuser_host,
                                          cfg->userService.randomuser_port);

    auto userService = std::make_shared<UserService>(cfg->userService, client);

    Api api;

    try
    {
        api.AddConfig(cfg->api)
            .AddController<HealthController>()
            .AddController<CatchAllController>()
            .AddController<UserController>(cfg->userService, userService)
            .Build();

        api.Run();
    }
    catch (std::invalid_argument ex)
    {
        CROW_LOG_DEBUG << "Something went wrong configuring api: " << ex.what();
        return -1;
    }
    catch (std::exception ex)
    {
        CROW_LOG_DEBUG << "Something went wrong with the api: " << ex.what();
        return -1;
    }

    CROW_LOG_DEBUG << "Shutting down API...";
    return 0;
}
