/*--------------------------------------------------------------------
 *  Copyright (c) Spudmash Media Pty Ltd. All rights reserved.
 *  Licensed under the MIT License.
 *  See License.txt in the project root for license information.
 *------------------------------------------------------------------*/

#pragma once

#include "api/app_types.hpp"
#include "dtos/error_response.hpp"
#include "utils/constants.hpp"
#include <crow.h>
#include <crow/logging.h>
#include <nlohmann/json.hpp>

namespace com_spudmash_cppuserapi::controllers
{

template <typename T, typename TGetQueryParams> class ControllerBase
{
  public:
    ~ControllerBase() = default;
    virtual void Init(api::CppUserApiApp &app) {};

    virtual TGetQueryParams ExtractGetQueryParameters(const crow::request &req)
    {
        TGetQueryParams p_;
        return p_;
    };

    template <typename Tex>
    void RegisterExceptionHandler(api::CppUserApiApp &app, crow::status code)
    {
        app.exception_handler(
            [code](crow::response &res)
            {
                CROW_LOG_DEBUG << "Current code: " << res.code;
                dtos::ErrorResponse err{};
                std::string msg{"See logs for details."};
                err.set_error(code, msg);

                res.add_header(utils::constants::HEADER_CONTENT_TYPE,
                               utils::constants::HEADER_JSON_CONTENT_TYPE);
                res.body = err.dump();
                res.end();
            });
    }

  private:
    virtual void RegisterGet(api::CppUserApiApp &app)
    {
        throw std::runtime_error("Feature not yet supported");
    };

    virtual void RegisterPost(api::CppUserApiApp &app)
    {
        throw std::runtime_error("Feature not yet supported");
    };

    virtual void RegisterUpdate(api::CppUserApiApp &app)
    {
        throw std::runtime_error("Feature not yet supported");
    };

    virtual void RegisterDelete(api::CppUserApiApp &app)
    {
        throw std::runtime_error("Feature not yet supported");
    };
};

} // namespace com_spudmash_cppuserapi::controllers
