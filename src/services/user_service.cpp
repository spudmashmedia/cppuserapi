/*--------------------------------------------------------------------
 *  Copyright (c) Spudmash Media Pty Ltd. All rights reserved.
 *  Licensed under the MIT License.
 *  See License.txt in the project root for license information.
 *------------------------------------------------------------------*/

// DEBUG MODE FOR JSON
#include <stdexcept>
#define JSON_DIAGNOSTICS 1

#define CROW_DISABLE_STATIC_DIR
#include "models/randomuser_response.hpp"
#include "models/user.hpp"
#include "services/base_service.hpp"
#include "services/user_service.h"
#include "utils/config/user_service_options.h"
#include "utils/http/http_client.hpp"

#include <crow/logging.h>
#include <format>
#include <optional>

namespace com_spudmash_cppuserapi::services
{

using namespace com_spudmash_cppuserapi::models;
using namespace com_spudmash_cppuserapi::utils::http;
using namespace com_spudmash_cppuserapi::utils::config;

UserService::UserService(const UserServiceOptions &cfg, std::shared_ptr<HttpClient> client)
    : cfg_(cfg), BaseService(std::move(client))
{
}

std::optional<models::User> UserService::First()
{
    CROW_LOG_DEBUG << "UserService::first: entered";

    try
    {
        auto response =
            http_client_->Get<models::RandomUserResponse>(RU_API_TEMPLATE_FIRST);

        if (!response.results.empty())
        {
            CROW_LOG_DEBUG << "UserService::first: got data";
            return response.results[0];
        }
    }
    catch (const nlohmann::json::exception &e)
    {
        CROW_LOG_DEBUG << "UserService::first: JSON exception " << e.what();

        return std::nullopt;
    }
    catch (const std::exception &e)
    {
        CROW_LOG_DEBUG << "UserService::first: exception " << e.what();

        return std::nullopt;
    }

    CROW_LOG_DEBUG << "UserService::first: exiting with no data";

    return std::nullopt;
}

std::optional<std::vector<models::User>> UserService::FindAll(int limit)
{
    CROW_LOG_DEBUG << "UserService::find_all: entered";
    if (limit <= 0)
    {
        throw std::invalid_argument(
            std::format("Limit must be greater than zero (0). Got: {}", limit));
    }

    try
    {
        std::string path = std::format(RU_API_TEMPLATE_ALL, limit);

        auto response = http_client_->Get<models::RandomUserResponse>(path);

        if (!response.results.empty())
        {
            CROW_LOG_DEBUG << "UserService::find_all: got data";
            return response.results;
        }
    }
    catch (const nlohmann::json::exception &e)
    {
        CROW_LOG_DEBUG << "UserService::find_all: JSON exception " << e.what();

        return std::nullopt;
    }
    catch (const std::exception &e)
    {
        CROW_LOG_DEBUG << "UserService::find_all: exception " << e.what();

        return std::nullopt;
    }

    CROW_LOG_DEBUG << "UserService::find_all: exiting with no data";

    return std::vector<models::User>{};
}

std::optional<models::User> UserService::FindById(int id)
{
    CROW_LOG_DEBUG << "UserService::find_by_id: entered";

    try
    {
        auto response = http_client_->Get<models::RandomUserResponse>(
            RU_API_TEMPLATE_DEFAULT);

        if (!response.results.empty())
        {
            CROW_LOG_DEBUG << "UserService::find_by_id: got data";
            return response.results[0];
        }
    }
    catch (const nlohmann::json::exception &e)
    {
        CROW_LOG_DEBUG << "UserService::find_by_id: JSON exception "
                       << e.what();

        return std::nullopt;
    }
    catch (const std::exception &e)
    {
        CROW_LOG_DEBUG << "UserService::find_by_id: exception " << e.what();

        return std::nullopt;
    }

    CROW_LOG_DEBUG << "UserService::find_by_id: exiting with no data";

    return std::nullopt;
}

} // namespace com_spudmash_cppuserapi::services
