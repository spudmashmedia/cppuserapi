/*--------------------------------------------------------------------
 *  Copyright (c) Spudmash Media Pty Ltd. All rights reserved.
 *  Licensed under the MIT License.
 *  See License.txt in the project root for license information.
 *------------------------------------------------------------------*/

#pragma once

#include "crow.h"
#include <crow/logging.h>
#include <nlohmann/json.hpp>

namespace com_spudmash_cppuserapi::controllers
{

template <typename T, typename TGetQueryParams> class ControllerBase
{
  public:
    ~ControllerBase() = default;
    virtual void Init(crow::SimpleApp &app) {};

    virtual TGetQueryParams ExtractGetQueryParameters(const crow::request &req)
    {
        TGetQueryParams p_;
        return p_;
    };

  private:
    virtual void RegisterGet(crow::SimpleApp &app) {};
    virtual void RegisterPost(crow::SimpleApp &app) {};
    virtual void RegisterUpdate(crow::SimpleApp &app) {};
    virtual void RegisterDelete(crow::SimpleApp &app) {};
};

} // namespace com_spudmash_cppuserapi::controllers
