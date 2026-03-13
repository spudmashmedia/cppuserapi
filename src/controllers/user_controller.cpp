/*--------------------------------------------------------------------
 *  Copyright (c) Spudmash Media Pty Ltd. All rights reserved.
 *  Licensed under the MIT License.
 *  See License.txt in the project root for license information.
 *------------------------------------------------------------------*/
#define CROW_DISABLE_STATIC_DIR
#include "controllers/get_user_query_param_request.h"
#include "controllers/user_controller.h"
#include "crow.h"
#include "dtos/mappers/user_response_mapper.hpp"
#include "dtos/user_response.hpp"
#include "services/user_service.h"
#include <crow/logging.h>
#include <nlohmann/json.hpp>
#include <string>

namespace com_spudmash_cppuserapi::controllers
{

using json = nlohmann::json;
using string = std::string;
using namespace com_spudmash_cppuserapi::services;
using namespace com_spudmash_cppuserapi::controllers;
using namespace com_spudmash_cppuserapi::dtos;
using namespace com_spudmash_cppuserapi::dtos::mappers;
using namespace com_spudmash_cppuserapi::utils::config;

inline constexpr std::string PARAM_COUNT = "count";

UserController::UserController(const ConfigResponse &cfg, UserService &svc)
    : cfg_(cfg), userService_(svc)
{
    CROW_LOG_DEBUG << "UserController - ctor";
}

void UserController::Init(api::CppUserApiApp &app)
{
    RegisterGet(app);
}

GetUserQueryParamRequest
UserController::ExtractGetQueryParameters(const crow::request &req)
{
    CROW_LOG_DEBUG << "ExtractGetUserParameters "
                   << req.url_params.keys().size();

    GetUserQueryParamRequest param;

    if (req.url_params.keys().size() == 0)
    {
        param.count = 1;
        return param;
    }

    auto count = std::string(req.url_params.get(PARAM_COUNT));

    param.count =
        count.empty()
            ? 1
            : std::atoi(count.c_str()); // default to 1 if no query string
    param.count = param.count > cfg_.randomuser_limit ? cfg_.randomuser_limit
                                                      : param.count;

    return param;
}

void UserController::RegisterGet(api::CppUserApiApp &app)
{
    CROW_LOG_DEBUG << "UserController::RegisterGet - entering";

    CROW_ROUTE(app, "/user")
        .methods(crow::HTTPMethod::GET)(
            [this](const crow::request &req)
            {
                CROW_LOG_DEBUG
                    << "UserController::RegisterGet - call user service";

                auto param = ExtractGetQueryParameters(req);

                CROW_LOG_DEBUG << "UserController::RegisterGet - count: "
                               << param.count;

                auto user_model = userService_.FindAll(param.count);

                if (!user_model)
                    return crow::response(crow::status::NOT_FOUND);

                CROW_LOG_DEBUG
                    << "UserController::RegisterGet - got user_model";

                UserResponse res;
                res = UserResponseMapper::MapFromUserModels(*user_model);

                return crow::response(crow::status::OK, res);
            });

    CROW_LOG_DEBUG << "UserController::RegisterGet - leaving";
}

} // namespace com_spudmash_cppuserapi::controllers
