/*--------------------------------------------------------------------
 *  Copyright (c) Spudmash Media Pty Ltd. All rights reserved.
 *  Licensed under the MIT License.
 *  See License.txt in the project root for license information.
 *------------------------------------------------------------------*/

#pragma once

#include "controllers/controller_base.hpp"
#include "controllers/get_generic_query_param_request.h"
#include "crow.h"

namespace com_spudmash_cppuserapi::controllers
{

class HealthController
    : public ControllerBase<HealthController, GetGenericQueryParamRequest>
{
  public:
    ~HealthController() = default;
    explicit HealthController();

    void RegisterGet(crow::SimpleApp &app) override;

  private:
};

} // namespace com_spudmash_cppuserapi::controllers
