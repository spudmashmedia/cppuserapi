/*--------------------------------------------------------------------
 *  Copyright (c) Spudmash Media Pty Ltd. All rights reserved.
 *  Licensed under the MIT License.
 *  See License.txt in the project root for license information.
 *------------------------------------------------------------------*/
#include <stdexcept>
#define CROW_DISABLE_STATIC_DIR
#include "controllers/get_user_query_param_request.h"
#include "controllers/user_controller.h"
#include "dtos/mappers/user_response_mapper.hpp"
#include "dtos/user_response.hpp"
#include "services/user_service.h"
#include "utils/config/user_service_options.h"

#include <crow.h>
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

UserController::UserController(UserServiceOptions cfg, std::shared_ptr<UserService> svc)
    : cfg_(std::move(cfg)), userService_(std::move(svc))
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

    // validate if parameter exists
    char *count_ptr = req.url_params.get(PARAM_COUNT);
    if (!count_ptr)
    {
        CROW_LOG_DEBUG << "ExtractGetUserParameters: cannot find count";
        param.count = 1;
        return param;
    }

    try
    {
        long validateLongCount =
            std::string(count_ptr).empty() ? 1 : std::stoll(count_ptr);

        auto validateIntCount = std::atoi(count_ptr);

        CROW_LOG_DEBUG << "Validating count: " << validateIntCount
                       << " against limit: " << cfg_.randomuser_limit;

        if (validateIntCount < 0 || validateIntCount > cfg_.randomuser_limit)
        {
            throw std::out_of_range(
                std::format("0 - {}", cfg_.randomuser_limit));
        }
        // pass validation, clamp with max limit
        param.count = validateIntCount;
    }
    catch (std::out_of_range &ex)
    {
        throw std::out_of_range(
            std::format("Value out of range. Got: {}", count_ptr));
    }
    catch (std::invalid_argument &ex)
    {
        throw std::invalid_argument(
            std::format("Invalid argument. Got: {}", count_ptr));
    }

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

                auto user_model = userService_->FindAll(param.count);

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
