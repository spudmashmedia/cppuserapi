/*--------------------------------------------------------------------
 *  Copyright (c) Spudmash Media Pty Ltd. All rights reserved.
 *  Licensed under the MIT License.
 *  See License.txt in the project root for license information.
 *------------------------------------------------------------------*/

#pragma once

#include "controllers/controller_base.hpp"
#include "controllers/get_user_query_param_request.h"
#include "crow.h"
#include "services/user_service.h"
#include "utils/config/config_response.hpp"

namespace com_spudmash_cppuserapi::controllers
{

class UserController
    : public ControllerBase<UserController, GetUserQueryParamRequest>
{
  public:
    ~UserController() = default;
    explicit UserController(const utils::config::ConfigResponse &cfg,
                            services::UserService &svc);
    void Init(crow::SimpleApp &app) override;

  private:
    const utils::config::ConfigResponse &cfg_;
    services::UserService &userService_;
    GetUserQueryParamRequest
    ExtractGetQueryParameters(const crow::request &req) override;
    void RegisterGet(crow::SimpleApp &app) override;
};

} // namespace com_spudmash_cppuserapi::controllers
