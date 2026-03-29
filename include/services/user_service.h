/*--------------------------------------------------------------------
 *  Copyright (c) Spudmash Media Pty Ltd. All rights reserved.
 *  Licensed under the MIT License.
 *  See License.txt in the project root for license information.
 *------------------------------------------------------------------*/

#pragma once

#include "models/user.hpp"
#include "services/base_service.hpp"
#include "utils/config/user_service_options.h"
#include "utils/http/http_client.hpp"

namespace com_spudmash_cppuserapi::services
{

class UserService : public BaseService
{
  public:
    ~UserService() = default;
    explicit UserService(utils::config::UserServiceOptions cfg,
                         std::shared_ptr<utils::http::HttpClient> client);

    std::optional<std::vector<models::User>> FindAll(int limit = 10) override;
    std::optional<models::User> First() override;
    std::optional<models::User> FindById(int id) override;

  private:
    static constexpr char RU_API_TEMPLATE_FIRST[]{"/api?results=1"};
    static constexpr char RU_API_TEMPLATE_ALL[]{"/api?results={}"};
    static constexpr char RU_API_TEMPLATE_DEFAULT[]{"/api"};

  protected:
    utils::config::UserServiceOptions cfg_;
};

} // namespace com_spudmash_cppuserapi::services
