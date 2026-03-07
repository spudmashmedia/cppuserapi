/*--------------------------------------------------------------------
 *  Copyright (c) Spudmash Media Pty Ltd. All rights reserved.
 *  Licensed under the MIT License.
 *  See License.txt in the project root for license information.
 *------------------------------------------------------------------*/

#pragma once

#define CROW_DISABLE_STATIC_DIR
#include "controllers/health_controller.h"
#include "controllers/user_controller.h"
#include "crow.h"
#include "services/user_service.h"
#include "utils/config/config_response.hpp"
#include "utils/http/http_client.h"

namespace com_spudmash_cppuserapi::api
{

class Api
{
  public:
    ~Api() = default;
    Api(const utils::config::ConfigResponse cfg);
    void Run();

  private:
    void Mount();
    crow::SimpleApp app_;

    utils::http::HttpClient httpClient_;

    services::UserService userService_;
    controllers::UserController userController_;

    controllers::HealthController healthController_;
    const utils::config::ConfigResponse cfg_;
};

} // namespace com_spudmash_cppuserapi::api
