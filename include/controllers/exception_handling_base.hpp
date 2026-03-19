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
#include <map>
#include <nlohmann/json.hpp>
#include <stdexcept>

namespace com_spudmash_cppuserapi::controllers
{

class ExceptionHandlingBase
{
  private:
    static inline std::map<std::type_index, int> dto_error_code_map_;

  public:
    ~ExceptionHandlingBase() = default;

    virtual void RegisterCatchAll(api::CppUserApiApp &app)
    {
        throw std::runtime_error("Feature not yet supported");
    };

    template <typename Tex> void AddHandler(crow::status code)
    {
        dto_error_code_map_[std::type_index(typeid(Tex))] = code;
    }

    // Registers a global exception handler for the API.
    //
    // Uses a "Type-to-Status" map to translate specific C++ exceptions
    // (e.g., std::invalid_argument) into appropriate HTTP status codes.
    //
    // Note: To preserve the original exception type and its 'what()' message,
    // a single re-throw is performed. This allows polymorphic resolution
    // without complex manual casting.
    void Finalise(api::CppUserApiApp &app)
    {
        app.exception_handler(
            [](crow::response &res)
            {
                int code{500};
                std::string msg{"See logs for details."};

                try
                {
                    throw; // simple throw to restore derived exception
                }
                catch (std::invalid_argument &ex)
                {
                    CROW_LOG_DEBUG << "invalid argument " << ex.what();
                    auto itr =
                        dto_error_code_map_.find(std::type_index(typeid(ex)));
                    if (itr != dto_error_code_map_.end())
                    {
                        code = itr->second;
                        msg = ex.what();
                    }
                }
                catch (std::out_of_range &ex)
                {
                    CROW_LOG_DEBUG << "out of range " << ex.what();
                    auto itr =
                        dto_error_code_map_.find(std::type_index(typeid(ex)));
                    if (itr != dto_error_code_map_.end())
                    {
                        code = itr->second;
                        msg = ex.what();
                    }
                }
                catch (std::exception &ex)
                {
                    CROW_LOG_DEBUG << "internal server error " << ex.what();
                    auto itr =
                        dto_error_code_map_.find(std::type_index(typeid(ex)));
                    if (itr != dto_error_code_map_.end())
                    {
                        code = itr->second;
                        msg = ex.what();
                    }
                }

                dtos::ErrorResponse err{};
                err.set_error(code, msg);

                res.add_header(utils::constants::HEADER_CONTENT_TYPE,
                               utils::constants::HEADER_JSON_CONTENT_TYPE);
                res.body = err.dump();
                res.end();
            });
    }
};

} // namespace com_spudmash_cppuserapi::controllers
