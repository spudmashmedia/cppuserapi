/*--------------------------------------------------------------------
 *  Copyright (c) Spudmash Media Pty Ltd. All rights reserved.
 *  Licensed under the MIT License.
 *  See License.txt in the project root for license information.
 *------------------------------------------------------------------*/

#pragma once
#include "utils/http/http_client.hpp"

#include <gmock/gmock.h>

namespace com_spudmash_cppuserapi::utils::http
{

class MockHttpClient : public HttpClient
{
  public:
    MOCK_METHOD(std::string,
                sendRequest,
                (boost::beast::http::verb method,
                 const std::string &target,
                 const std::string &body),
                (override));
};

} // namespace com_spudmash_cppuserapi::utils::http
