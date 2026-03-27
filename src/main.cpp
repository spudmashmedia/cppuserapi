/*--------------------------------------------------------------------
 *  Copyright (c) Spudmash Media Pty Ltd. All rights reserved.
 *  Licensed under the MIT License.
 *  See License.txt in the project root for license information.
 *------------------------------------------------------------------*/
#include "api/api.h"
// #include "controllers/catch_all_controller.h"
// #include "controllers/health_controller.h"
// #include "controllers/user_controller.h"
// #include "services/user_service.h"
#include "utils/config/config.hpp"
#include "utils/config/config_response.hpp"
#include "utils/http/boost_http_client.h"

#include <stdexcept>

using namespace com_spudmash_cppuserapi::api;
using namespace com_spudmash_cppuserapi::utils::config;
using namespace com_spudmash_cppuserapi::utils::http;
// using namespace com_spudmash_cppuserapi::services;
// using namespace com_spudmash_cppuserapi::controllers;

int main()
{
    // Bootstrap dependencies - Singletons use shared pointers
    auto cfg =
        std::make_shared<ConfigResponse>(Config::read_config());
    auto client =
        std::make_shared<BoostHttpClient>(cfg->randomuser_host,
                                          cfg->randomuser_port);

    // TODO: create shared resource for userService
    // auto userService = std::make_shared<services::UserService>(cfg, client);

    Api api;

    try
    {
        api.AddConfig(cfg)
            .AddHttpClient(client)
            // .AddService<UserServices>()
            // .AddController<HealthController>()
            // .AddController<CatchAllController>()
            // .AddController<UserController>()
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
