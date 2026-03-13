/*--------------------------------------------------------------------
 *  Copyright (c) Spudmash Media Pty Ltd. All rights reserved.
 *  Licensed under the MIT License.
 *  See License.txt in the project root for license information.
 *------------------------------------------------------------------*/

#pragma once
#include "middleware/correlation_id_middleware.hpp"

namespace com_spudmash_cppuserapi::api
{

using CppUserApiApp = crow::App<middleware::CorrelationIdMiddleware>;

}
