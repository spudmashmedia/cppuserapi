/*--------------------------------------------------------------------
 *  Copyright (c) Spudmash Media Pty Ltd. All rights reserved.
 *  Licensed under the MIT License.
 *  See License.txt in the project root for license information.
 *------------------------------------------------------------------*/
#pragma once

#include <string>

namespace com_spudmash_cppuserapi::utils::config
{

struct ConfigResponse
{
    // Server
    int port{8080};
    int concurrency{20};

    // Random User Endpoint
    int randomuser_limit{10};
    std::string randomuser_host{"randomuser.me"};
    std::string randomuser_port{"443"};
    std::string randomuser_path_api{"/api"};
};

} // namespace com_spudmash_cppuserapi::utils::config
