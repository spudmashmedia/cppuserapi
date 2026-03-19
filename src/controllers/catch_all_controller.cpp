/*--------------------------------------------------------------------
 *  Copyright (c) Spudmash Media Pty Ltd. All rights reserved.
 *  Licensed under the MIT License.
 *  See License.txt in the project root for license information.
 *------------------------------------------------------------------*/
#define CROW_DISABLE_STATIC_DIR

#include "controllers/catch_all_controller.h"
#include "controllers/exception_handling_base.hpp"
#include "dtos/error_response.hpp"
#include <crow.h>
#include <crow/logging.h>
#include <nlohmann/json.hpp>
#include <string>

namespace com_spudmash_cppuserapi::controllers
{

using json = nlohmann::json;
using string = std::string;
using namespace com_spudmash_cppuserapi::controllers;

inline constexpr std::string PARAM_COUNT = "count";

CatchAllController::CatchAllController()
{
    CROW_LOG_DEBUG << "CatchAllController - ctor";
}

void CatchAllController::Init(api::CppUserApiApp &app)
{
    RegisterCatchAll(app);

    ExceptionHandlingBase::AddHandler<std::invalid_argument>(
        crow::status::BAD_REQUEST);
    ExceptionHandlingBase::AddHandler<std::out_of_range>(
        crow::status::BAD_REQUEST);
    ExceptionHandlingBase::AddHandler<std::exception>(
        crow::status::INTERNAL_SERVER_ERROR);
    ExceptionHandlingBase::Finalise(app);
}

void CatchAllController::RegisterCatchAll(api::CppUserApiApp &app)
{
    CROW_LOG_DEBUG << "UserController::RegisterGet - entering";

    CROW_CATCHALL_ROUTE(app)(
        [this](crow::response &res)
        {
            dtos::ErrorResponse err{};
            std::string msg{"See logs for details."};
            err.set_error(crow::status::BAD_REQUEST, msg);
            res.add_header(constants::HEADER_CONTENT_TYPE,
                           constants::HEADER_JSON_CONTENT_TYPE);
            res.body = err.dump();
            res.end();
        });
}

} // namespace com_spudmash_cppuserapi::controllers
