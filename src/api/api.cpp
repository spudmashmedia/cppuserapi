/*--------------------------------------------------------------------
 *  Copyright (c) Spudmash Media Pty Ltd. All rights reserved.
 *  Licensed under the MIT License.
 *  See License.txt in the project root for license information.
 *------------------------------------------------------------------*/

#define CROW_DISABLE_STATIC_DIR

#include "api/api.h"
#include "controllers/catch_all_controller.h"
#include "controllers/health_controller.h"
#include "controllers/user_controller.h"
#include "utils/config/config_response.hpp"
#include "utils/http/http_client.h"

#include <crow.h>

namespace com_spudmash_cppuserapi::api
{

using namespace com_spudmash_cppuserapi::controllers;
using namespace com_spudmash_cppuserapi::utils::config;
using namespace com_spudmash_cppuserapi::utils::http;

Api &Api::AddConfig(std::shared_ptr<ConfigResponse> cfg)
{
    cfg_ = std::move(cfg);
    return *this;
}

Api &Api::AddHttpClient(std::shared_ptr<HttpClient> client)
{
    httpClient_ = std::move(client);
    return *this;
}

void Api::Build()
{
    catchAllController_.Init(app_);
    healthController_.Init(app_);
    // userController_.Init(app_);
}

void Api::Run()
{
    app_.loglevel(crow::LogLevel::Debug);
    app_.debug_print();
    app_.port(cfg_->port)
        .multithreaded()
        .concurrency(cfg_->concurrency)
        .run();
}

} // namespace com_spudmash_cppuserapi::api
