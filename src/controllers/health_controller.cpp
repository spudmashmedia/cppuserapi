/*--------------------------------------------------------------------
 *  Copyright (c) Spudmash Media Pty Ltd. All rights reserved.
 *  Licensed under the MIT License.
 *  See License.txt in the project root for license information.
 *------------------------------------------------------------------*/

#define CROW_DISABLE_STATIC_DIR
#include "controllers/health_controller.h"
#include "crow.h"
#include "crow/logging.h"
#include "dtos/health_response.hpp"
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

void HealthController::RegisterGet(crow::SimpleApp &app)
{
    CROW_LOG_DEBUG << "HealthController::RegisterGet - entering";

    HealthResponse res;
    res.status = "OK";

    CROW_ROUTE(app, "/health")
        .methods(crow::HTTPMethod::GET)(
            [res]()
            {
                return crow::response(crow::status::OK, "application/json",
                                      res.serialize().dump());
            });

    CROW_LOG_DEBUG << "HealthController::RegisterGet - leaving";
}

} // namespace com_spudmash_cppuserapi::controllers
