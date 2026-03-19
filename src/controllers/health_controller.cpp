/*--------------------------------------------------------------------
 *  Copyright (c) Spudmash Media Pty Ltd. All rights reserved.
 *  Licensed under the MIT License.
 *  See License.txt in the project root for license information.
 *------------------------------------------------------------------*/

#define CROW_DISABLE_STATIC_DIR
#include "controllers/health_controller.h"
#include "dtos/health_response.hpp"
#include <crow.h>
#include <crow/logging.h>
#include <nlohmann/json.hpp>
#include <string>

namespace com_spudmash_cppuserapi::controllers
{

using json = nlohmann::json;
using string = std::string;
using namespace com_spudmash_cppuserapi::controllers;
using namespace com_spudmash_cppuserapi::dtos;

HealthController::HealthController()
{
    CROW_LOG_DEBUG << "HealthController - ctor";
}

void HealthController::Init(api::CppUserApiApp &app)
{
    RegisterGet(app);
}

void HealthController::RegisterGet(api::CppUserApiApp &app)
{
    CROW_LOG_DEBUG << "HealthController::RegisterGet - entering";

    const HealthResponse res{};

    CROW_ROUTE(app, "/health")
        .methods(crow::HTTPMethod::GET)([res]() { return res; });

    CROW_LOG_DEBUG << "HealthController::RegisterGet - leaving";
}

} // namespace com_spudmash_cppuserapi::controllers
