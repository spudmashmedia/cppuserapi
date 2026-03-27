/*--------------------------------------------------------------------
 *  Copyright (c) Spudmash Media Pty Ltd. All rights reserved.
 *  Licensed under the MIT License.
 *  See License.txt in the project root for license information.
 *------------------------------------------------------------------*/
#pragma once

#define CROW_DISABLE_STATIC_DIR
#include "controllers/catch_all_controller.h"
#include "controllers/health_controller.h"
#include "controllers/user_controller.h"
#include "services/user_service.h"
#include "utils/config/config_response.hpp"
#include "utils/http/http_client.h"

#include <crow.h>

namespace com_spudmash_cppuserapi::api
{

using namespace com_spudmash_cppuserapi::middleware;

class Api
{
  public:
    ~Api() = default;
    Api &AddConfig(std::shared_ptr<utils::config::ConfigResponse> cfg);
    Api &AddHttpClient(std::shared_ptr<utils::http::HttpClient> client);
    void Build();
    void Run();

  private:
    api::CppUserApiApp app_; // See include/api/app_type.hpp

    std::shared_ptr<utils::config::ConfigResponse> cfg_;
    std::shared_ptr<utils::http::HttpClient> httpClient_;

    controllers::CatchAllController catchAllController_;
    controllers::HealthController healthController_;

    // services::UserService userService_;
    // controllers::UserController userController_;
};

} // namespace com_spudmash_cppuserapi::api
