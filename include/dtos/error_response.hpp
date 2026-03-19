/*--------------------------------------------------------------------
 *  Copyright (c) Spudmash Media Pty Ltd. All rights reserved.
 *  Licensed under the MIT License.
 *  See License.txt in the project root for license information.
 *------------------------------------------------------------------*/

#pragma once

#include "dtos/json_response_base.hpp"
#include <crow.h>
#include <nlohmann/json.hpp>
#include <string>

namespace com_spudmash_cppuserapi::dtos
{

class ErrorResponse : public JsonResponseBase<ErrorResponse>
{
  public:
    void set_error(const int &code = 200, const std::string &msg = "")
    {
        JsonResponseBase::set_error(code, msg);
    }

    std::string dump() const
    {
        return JsonResponseBase::dump();
    };
};

} // namespace com_spudmash_cppuserapi::dtos
