/*--------------------------------------------------------------------
 *  Copyright (c) Spudmash Media Pty Ltd. All rights reserved.
 *  Licensed under the MIT License.
 *  See License.txt in the project root for license information.
 *------------------------------------------------------------------*/
#pragma once

#include <string>

namespace com_spudmash_cppuserapi::utils::config
{

struct ApiOptions
{
    // Server
    int port{8080};
    int concurrency{20};
};

} // namespace com_spudmash_cppuserapi::utils::config
