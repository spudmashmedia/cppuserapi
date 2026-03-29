/*--------------------------------------------------------------------
 *  Copyright (c) Spudmash Media Pty Ltd. All rights reserved.
 *  Licensed under the MIT License.
 *  See License.txt in the project root for license information.
 *------------------------------------------------------------------*/

#pragma once
#include <nlohmann/json.hpp>

namespace com_spudmash_cppuserapi::tests::mocks
{

struct UserDataMocks
{
    static inline nlohmann::json USER_RESULTS_ZERO_ = {
        {"results", nlohmann::json::array()},
        {"info", {{"seed", "generated"}, {"results", 0}, {"page", 1}, "version", "1.4"}}};

    static inline nlohmann::json BAD_JSON_ = R"(
        {"rez-SaLTS":[],
            "infoMATION":{"seed":"152dfb04b2d5f5ee","results":1,"page":1,"version":"1.4"}
        }
    )";

    static inline nlohmann::json GenerateData(int count)
    {
        nlohmann::json data;

        // build info node
        data["info"] = {{"seed", "generated"}, {"results", count}, {"page", 1}, {"version", "1.4"}};

        // build results node
        for (auto i = 0; i < count; i++)
        {
            data["results"]
                .push_back({{"gender", "female"},
                            {"name", {{"title", "Miss"}, {"first", "Anna"}, {"last", "Yamada"}}},
                            {"location", {{"street", {{"number", 2}, {"name", "Snack Aisle Ave"}}}, {"city", "Meguro"}, {"state", "Tokyo"}, {"country", "Japan"}, {"postcode", 1530063}, {"coordinates", {{"latitude", "35.6339"}, {"longitude", "139.7081"}}}, {"timezone", {{"offset", "+9:00"}, {"description", "Tokyo"}}}}},
                            {"email", "anna.yamada@line.com"},
                            {"login", {{"uuid", "661f9511-f30c-5e55-b827-557766551111"}, {"username", "akino_anna_official"}, {"password", "RocketEngineValve"}, {"salt", "salt2"}, {"md5", "md5_2"}, {"sha1", "sha1_2"}, {"sha256", "sha256_2"}}},
                            {"dob", {{"date", "2008-09-10T00:00:00.000Z"}, {"age", 16}}},
                            {"registered", {{"date", "2023-02-01T00:00:00.000Z"}, {"age", 1}}},
                            {"phone", "03-8765-4321"},
                            {"cell", "080-8765-4321"},
                            {"id", {{"name", "ID"}, {"value", "2024-002"}}},
                            {"picture", {{"large", "https://anilist.co/character/174190/Anna-Yamada"}, {"medium", "https://anilist.co/character/174190/Anna-Yamada"}, {"thumbnail", "https://anilist.co/character/174190/Anna-Yamada"}}},
                            {"nat", "JP"}});
        }

        return data;
    }
};

} // namespace com_spudmash_cppuserapi::tests::mocks
