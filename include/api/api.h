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
    Api(const utils::config::ConfigResponse cfg);
    void Run();

  private:
    void Mount();
    api::CppUserApiApp app_; // See include/api/app_type.hpp

    utils::http::HttpClient httpClient_;

    controllers::CatchAllController catchAllController_;

    services::UserService userService_;
    controllers::UserController userController_;

    controllers::HealthController healthController_;
    const utils::config::ConfigResponse cfg_;
};

} // namespace com_spudmash_cppuserapi::api
