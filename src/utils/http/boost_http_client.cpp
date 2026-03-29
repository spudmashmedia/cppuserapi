/*--------------------------------------------------------------------
 *  Copyright (c) Spudmash Media Pty Ltd. All rights reserved.
 *  Licensed under the MIT License.
 *  See License.txt in the project root for license information.
 *------------------------------------------------------------------*/

#include "utils/http/boost_http_client.h"
#include <boost/asio/connect.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/ssl.hpp>
#include <crow/logging.h>

namespace com_spudmash_cppuserapi::utils::http
{

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
namespace ssl = net::ssl;
using tcp = net::ip::tcp;
using string = std::string;

BoostHttpClient::BoostHttpClient(string host, string port)
    : host_(std::move(host)), port_(std::move(port)),
      ctx_(ssl::context::tlsv12_client)
{
}

string BoostHttpClient::sendRequest(http::verb method, const string &target,
                                    const string &body)
{
    net::io_context ioc;
    tcp::resolver resolver(ioc);
    beast::ssl_stream<beast::tcp_stream> stream(ioc, ctx_);

    if (!SSL_set_tlsext_host_name(stream.native_handle(), host_.c_str()))
        throw beast::system_error(
            beast::error_code(static_cast<int>(::ERR_get_error()),
                              net::error::get_ssl_category()));

    auto const results = resolver.resolve(host_, port_);
    beast::get_lowest_layer(stream).connect(results);
    stream.handshake(ssl::stream_base::client);

    http::request<http::string_body> req{method, target, 11};
    req.set(http::field::host, host_);
    req.set(http::field::user_agent, "CppUserApi/1.0.0");

    if (!body.empty())
    {
        req.body() = body;
        req.prepare_payload();
    }

    http::write(stream, req);
    beast::flat_buffer buffer;
    http::response<http::string_body> res;
    http::read(stream, buffer, res);

    beast::error_code ec;
    [[maybe_unused]] auto _ = stream.shutdown(ec);
    if (ec)
    {
        CROW_LOG_WARNING << "Stream shutdown info: " << ec.message();
    }
    return res.body();
}

} // namespace com_spudmash_cppuserapi::utils::http
