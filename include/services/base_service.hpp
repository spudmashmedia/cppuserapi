/*--------------------------------------------------------------------
 *  Copyright (c) Spudmash Media Pty Ltd. All rights reserved.
 *  Licensed under the MIT License.
 *  See License.txt in the project root for license information.
 *------------------------------------------------------------------*/

#pragma once

#include "models/user.hpp"
#include "utils/http/http_client.hpp"

namespace com_spudmash_cppuserapi::services
{

class BaseService
{
  public:
    ~BaseService() = default;

    virtual std::optional<std::vector<models::User>> FindAll(int limit = 10);
    virtual std::optional<models::User> First();
    virtual std::optional<models::User> FindById(int id);

    // Remove any operators from interface
    BaseService(const BaseService &) = delete;
    BaseService &operator=(const BaseService &) = delete;

  protected:
    explicit BaseService(std::shared_ptr<utils::http::HttpClient> client)
        : http_client_(std::move(client))
    {
    }

    std::shared_ptr<utils::http::HttpClient> http_client_;
};

} // namespace com_spudmash_cppuserapi::services
