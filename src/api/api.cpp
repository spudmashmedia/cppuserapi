/*--------------------------------------------------------------------
 *  Copyright (c) Spudmash Media Pty Ltd. All rights reserved.
 *  Licensed under the MIT License.
 *  See License.txt in the project root for license information.
 *------------------------------------------------------------------*/

#include <stdexcept>
#define CROW_DISABLE_STATIC_DIR

#include "api/api.h"
#include "controllers/controller.h"
#include "utils/config/api_options.h"

#include <crow.h>

namespace com_spudmash_cppuserapi::api
{

using namespace com_spudmash_cppuserapi::controllers;
using namespace com_spudmash_cppuserapi::utils::config;

Api &Api::AddConfig(utils::config::ApiOptions cfg)
{
    cfg_ = std::move(cfg);
    return *this;
}

void Api::Build()
{
    if (controllers_.size() <= 0)
    {
        throw std::invalid_argument("No Controllers Registered");
    }

    for (const auto &c : controllers_)
    {
        c->Init(app_);
    }
}

void Api::Run()
{
    app_.loglevel(crow::LogLevel::Debug);
    app_.debug_print();
    app_.port(cfg_.port)
        .multithreaded()
        .concurrency(cfg_.concurrency)
        .run();
}

} // namespace com_spudmash_cppuserapi::api
