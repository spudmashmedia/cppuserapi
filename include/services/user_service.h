/*--------------------------------------------------------------------
 *  Copyright (c) Spudmash Media Pty Ltd. All rights reserved.
 *  Licensed under the MIT License.
 *  See License.txt in the project root for license information.
 *------------------------------------------------------------------*/

#pragma once

#include "models/user.hpp"
#include "utils/config/config_response.hpp"
#include "utils/http/http_client.h"

namespace com_spudmash_cppuserapi::services
{

class UserService
{
  public:
    ~UserService() = default;
    explicit UserService(const utils::config::ConfigResponse &cfg,
                         utils::http::HttpClient &client);

    std::optional<std::vector<models::User>> FindAll(int limit = 10);
    std::optional<models::User> First();
    std::optional<models::User> FindById(int id);

  private:
    const utils::config::ConfigResponse &cfg_;
    utils::http::HttpClient &http_client_;
};

} // namespace com_spudmash_cppuserapi::services
