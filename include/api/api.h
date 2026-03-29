/*--------------------------------------------------------------------
 *  Copyright (c) Spudmash Media Pty Ltd. All rights reserved.
 *  Licensed under the MIT License.
 *  See License.txt in the project root for license information.
 *------------------------------------------------------------------*/
#pragma once

#define CROW_DISABLE_STATIC_DIR

#include "controllers/controller.h"
#include "utils/config/api_options.h"

#include <crow.h>

namespace com_spudmash_cppuserapi::api
{

class Api
{
  public:
    ~Api() = default;
    Api &AddConfig(utils::config::ApiOptions cfg);

    template <typename T, typename... Args>
    Api &AddController(Args &&...args)
    {
        controllers_.push_back(std::make_unique<T>(std::forward<Args>(args)...));
        return *this;
    }

    void Build();
    void Run();

  private:
    api::CppUserApiApp app_; // See include/api/app_type.hpp
    utils::config::ApiOptions cfg_;
    std::vector<std::unique_ptr<controllers::Controller>> controllers_;
};

} // namespace com_spudmash_cppuserapi::api
