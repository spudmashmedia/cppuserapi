/*--------------------------------------------------------------------
 *  Copyright (c) Spudmash Media Pty Ltd. All rights reserved.
 *  Licensed under the MIT License.
 *  See License.txt in the project root for license information.
 *------------------------------------------------------------------*/
#pragma once

#include "utils/http/http_client.h"
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/ssl.hpp>
#include <nlohmann/json.hpp>
#include <string>

namespace com_spudmash_cppuserapi::utils::http
{

class BoostHttpClient : public HttpClient
{
  public:
    explicit BoostHttpClient(std::string host, std::string port = "443");

    template <typename T> T Get(const std::string &target)
    {
        std::string raw =
            sendRequest(boost::beast::http::verb::get, target, "");
        return nlohmann::json::parse(raw).get<T>();
    }

    template <typename T>
    T Post(const std::string &target, const std::string &body)
    {
        std::string raw =
            sendRequest(boost::beast::http::verb::post, target, body);
        return nlohmann::json::parse(raw).get<T>();
    }

  private:
    std::string host_;
    std::string port_;
    boost::asio::ssl::context ctx_;

  protected:
    std::string sendRequest(boost::beast::http::verb method,
                            const std::string &target,
                            const std::string &body) override;
};

} // namespace com_spudmash_cppuserapi::utils::http
