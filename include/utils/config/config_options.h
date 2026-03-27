/*--------------------------------------------------------------------
 *  Copyright (c) Spudmash Media Pty Ltd. All rights reserved.
 *  Licensed under the MIT License.
 *  See License.txt in the project root for license information.
 *------------------------------------------------------------------*/
#pragma once

#include "utils/config/api_options.h"
#include "utils/config/user_service_options.h"

namespace com_spudmash_cppuserapi::utils::config
{

struct ConfigResponse
{
    ApiOptions api;
    UserServiceOptions userService;
};

} // namespace com_spudmash_cppuserapi::utils::config
