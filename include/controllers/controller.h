/*--------------------------------------------------------------------
 *  Copyright (c) Spudmash Media Pty Ltd. All rights reserved.
 *  Licensed under the MIT License.
 *  See License.txt in the project root for license information.
 *------------------------------------------------------------------*/

#pragma once

#include "api/app_types.hpp"

#include <crow.h>
#include <crow/logging.h>
#include <nlohmann/json.hpp>

namespace com_spudmash_cppuserapi::controllers
{

class Controller
{
  public:
    virtual ~Controller() = default;
    virtual void Init(api::CppUserApiApp &app) = 0;
};

} // namespace com_spudmash_cppuserapi::controllers
