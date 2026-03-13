/*--------------------------------------------------------------------
 *  Copyright (c) Spudmash Media Pty Ltd. All rights reserved.
 *  Licensed under the MIT License.
 *  See License.txt in the project root for license information.
 *------------------------------------------------------------------*/

#pragma once

#include "api/app_types.hpp"
#include "crow.h"
#include <crow/logging.h>
#include <nlohmann/json.hpp>

namespace com_spudmash_cppuserapi::controllers
{

template <typename T, typename TGetQueryParams> class ControllerBase
{
  public:
    ~ControllerBase() = default;
    virtual void Init(api::CppUserApiApp &app) {};

    virtual TGetQueryParams ExtractGetQueryParameters(const crow::request &req)
    {
        TGetQueryParams p_;
        return p_;
    };

  private:
    virtual void RegisterGet(api::CppUserApiApp &app) {};
    virtual void RegisterPost(api::CppUserApiApp &app) {};
    virtual void RegisterUpdate(api::CppUserApiApp &app) {};
    virtual void RegisterDelete(api::CppUserApiApp &app) {};
};

} // namespace com_spudmash_cppuserapi::controllers
