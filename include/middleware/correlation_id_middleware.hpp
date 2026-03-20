/*--------------------------------------------------------------------
 *  Copyright (c) Spudmash Media Pty Ltd. All rights reserved.
 *  Licensed under the MIT License.
 *  See License.txt in the project root for license information.
 *------------------------------------------------------------------*/
#pragma once

#include "utils/constants.hpp"
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <crow.h>
#include <string>

namespace com_spudmash_cppuserapi::middleware
{

static inline const std::string DEFAULT_ID{"NO_ID"};
static inline const int MAX_LENGTH{64};

struct CorrelationIdMiddleware
{
    struct context
    {
        std::string correlation_id;
    };

    bool isValidLength(const std::string *src)
    {
        if (src == nullptr || src->empty())
            return false;

        return src->length() <= MAX_LENGTH;
    }

    bool isValidUuid(const std::string *src)
    {
        if (src == nullptr || src->empty())
            return false;

        auto is_valid = false;

        try
        {
            boost::uuids::string_generator gen_from_str;
            gen_from_str(src->c_str());
            is_valid = true;
        }
        catch (...)
        {
            is_valid = false;
        }
        return is_valid;
    }

    void before_handle(crow::request &req, crow::response &res, context &ctx)
    {
        auto header_wip =
            req.get_header_value(utils::constants::CORRELATION_ID_HEADER);
        static thread_local boost::uuids::random_generator gen;

        // Validation - fast fail
        if (header_wip.empty())
        {
            ctx.correlation_id = boost::uuids::to_string(gen());
            return;
        }

        if (!isValidLength(&header_wip))
        {
            CROW_LOG_WARNING << "Santized oversized Correlation Id";
            ctx.correlation_id = boost::uuids::to_string(gen());
            return;
        }

        if (!isValidUuid(&header_wip))
        {
            CROW_LOG_WARNING << "Santized malformed Correlation Id";
            ctx.correlation_id = boost::uuids::to_string(gen());
            return;
        }

        // validation passed
        ctx.correlation_id = header_wip;
    }

    void after_handle(crow::request &req, crow::response &res, context &ctx)
    {
        res.set_header(utils::constants::CORRELATION_ID_HEADER,
                       ctx.correlation_id);
    }
};

} // namespace com_spudmash_cppuserapi::middleware
