/*--------------------------------------------------------------------
 *  Copyright (c) Spudmash Media Pty Ltd. All rights reserved.
 *  Licensed under the MIT License.
 *  See License.txt in the project root for license information.
 *------------------------------------------------------------------*/
#include "api/api.h"
#include "utils/config/config.hpp"
#include "utils/config/config_response.hpp"

using namespace com_spudmash_cppuserapi::api;
using namespace com_spudmash_cppuserapi::utils::config;

int main()
{
    // load config
    auto cfg = Config::read_config();

    Api api{cfg};
    api.Run();
}
