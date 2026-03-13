/*--------------------------------------------------------------------
 *  Copyright (c) Spudmash Media Pty Ltd. All rights reserved.
 *  Licensed under the MIT License.
 *  See License.txt in the project root for license information.
 *------------------------------------------------------------------*/

#define CROW_DISABLE_STATIC_DIR
#include "api/api.h"
#include "controllers/health_controller.h"
#include "controllers/user_controller.h"
#include "crow.h"
#include "utils/config/config_response.hpp"

namespace com_spudmash_cppuserapi::api
{

using namespace com_spudmash_cppuserapi::controllers;
using namespace com_spudmash_cppuserapi::utils::config;

Api::Api(const ConfigResponse cfg)
    : cfg_(cfg), httpClient_(cfg.randomuser_host, cfg.randomuser_port),
      userService_(cfg, httpClient_), userController_(cfg, userService_),
      healthController_()
{
    Mount();
}

void Api::Mount()
{
    userController_.Init(app_);
    healthController_.Init(app_);
}

void Api::Run()
{
    app_.debug_print();
    app_.port(cfg_.port)
        .multithreaded()
        .concurrency(cfg_.concurrency)
        .loglevel(crow::LogLevel::Debug)
        .run();
}

} // namespace com_spudmash_cppuserapi::api
