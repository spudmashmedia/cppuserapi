/*--------------------------------------------------------------------
 *  Copyright (c) Spudmash Media Pty Ltd. All rights reserved.
 *  Licensed under the MIT License.
 *  See License.txt in the project root for license information.
 *------------------------------------------------------------------*/

#pragma once

#include "api/app_types.hpp"
#include "controllers/controller_base.hpp"
#include "controllers/exception_handling_base.hpp"
#include "controllers/get_generic_query_param_request.h"

namespace com_spudmash_cppuserapi::controllers
{

using namespace com_spudmash_cppuserapi::utils;
using namespace com_spudmash_cppuserapi::api;

class CatchAllController
    : public ControllerBase<CatchAllController, GetGenericQueryParamRequest>,
      public ExceptionHandlingBase
{
  public:
    ~CatchAllController() = default;
    explicit CatchAllController();
    void Init(api::CppUserApiApp &app) override;

  private:
    void RegisterCatchAll(api::CppUserApiApp &app) override;
};

} // namespace com_spudmash_cppuserapi::controllers
