/*--------------------------------------------------------------------
 *  Copyright (c) Spudmash Media Pty Ltd. All rights reserved.
 *  Licensed under the MIT License.
 *  See License.txt in the project root for license information.
 *------------------------------------------------------------------*/

#pragma once

#include "api/app_types.hpp"
#include "controllers/controller_base.hpp"
#include "controllers/get_user_query_param_request.h"
#include "services/user_service.h"
#include "utils/config/config_response.hpp"
#include <crow.h>

namespace com_spudmash_cppuserapi::controllers
{

class UserController
    : public ControllerBase<UserController, GetUserQueryParamRequest>
{
  public:
    ~UserController() = default;
    explicit UserController(const utils::config::ConfigResponse &cfg,
                            services::UserService &svc);
    void Init(api::CppUserApiApp &app) override;

  private:
    static constexpr char PARAM_COUNT[]{"count"};

    const utils::config::ConfigResponse cfg_;
    services::UserService &userService_;

    GetUserQueryParamRequest
    ExtractGetQueryParameters(const crow::request &req) override;
    void RegisterGet(api::CppUserApiApp &app) override;
};

} // namespace com_spudmash_cppuserapi::controllers
