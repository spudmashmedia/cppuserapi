/*--------------------------------------------------------------------
 *  Copyright (c) Spudmash Media Pty Ltd. All rights reserved.
 *  Licensed under the MIT License.
 *  See License.txt in the project root for license information.
 *------------------------------------------------------------------*/

#include "mocks/utils/http/mock_http_client.hpp"
#include "models/user.hpp"
#include "services/user_service.h"
#include "utils/config/user_service_options.h"

#include <boost/beast/http.hpp>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace com_spudmash_cppuserapi::services
{

namespace
{
using boost::beast::http::verb;
using ::testing::_;
using ::testing::An;
using ::testing::Return;

class UserServiceTest : public ::testing::Test
{
  protected:
    utils::config::UserServiceOptions mock_cfg_;
    std::shared_ptr<utils::http::MockHttpClient> mock_client_;
    std::unique_ptr<services::UserService> sut_;

    void SetUp()
    {
        mock_client_ = std::make_shared<utils::http::MockHttpClient>();
        sut_ = std::make_unique<services::UserService>(mock_cfg_, mock_client_);
    }
};

TEST_F(UserServiceTest, FindAll_2_Should_return_2_users)
{
    // Arrange
    // std::string mockResponse = R"({"results":[{"gender":"female","name":{"title":"Miss","first":"Silje","last":"Pedersen"},"location":{"street":{"number":7655,"name":"Nordsøvej"},"city":"Viby J.","state":"Sjælland","country":"Denmark","postcode":67645,"coordinates":{"latitude":"-38.6713","longitude":"37.4389"},"timezone":{"offset":"+5:45","description":"Kathmandu"}},"email":"silje.pedersen@example.com","login":{"uuid":"db4cc9fc-af78-4073-a59a-33d7b41d4ca0","username":"redelephant308","password":"monkey1","salt":"8CGcCoAw","md5":"6a052cce2e68e6417eab5174ec5c5390","sha1":"7199d69bab2e7b5c41c83516ee30bc8d56491c62","sha256":"b48adb245072658f5dbc53946b839bd2be5df12a3d362310fe103acb62ce60bc"},"dob":{"date":"1992-07-27T13:15:54.358Z","age":33},"registered":{"date":"2012-02-18T03:22:44.502Z","age":14},"phone":"20827609","cell":"23508048","id":{"name":"CPR","value":"270792-9503"},"picture":{"large":"https://randomuser.me/api/portraits/women/70.jpg","medium":"https://randomuser.me/api/portraits/med/women/70.jpg","thumbnail":"https://randomuser.me/api/portraits/thumb/women/70.jpg"},"nat":"DK"},{"gender":"male","name":{"title":"Mr","first":"Hugo","last":"Costa"},"location":{"street":{"number":5046,"name":"Rua Vinte E Um"},"city":"Jequié","state":"Piauí","country":"Brazil","postcode":73417,"coordinates":{"latitude":"85.7252","longitude":"-76.8088"},"timezone":{"offset":"+9:00","description":"Tokyo, Seoul, Osaka, Sapporo, Yakutsk"}},"email":"hugo.costa@example.com","login":{"uuid":"680d17cf-8140-4073-a8f7-ab77d98f8a2a","username":"purplelion868","password":"bonsai","salt":"BE2JH7GP","md5":"6d233c1b1e57cb12700094372bd5da88","sha1":"f8c982763189f29c7f8a483efc4915a0771ecd52","sha256":"5fd9f64078b5116b7c691d89590e367cc2f663134e0d937f0f8eeb86952ed401"},"dob":{"date":"1967-12-09T13:57:46.677Z","age":58},"registered":{"date":"2006-04-06T05:42:12.223Z","age":19},"phone":"(57) 1266-0530","cell":"(82) 7515-3544","id":{"name":"CPF","value":"169.027.829-34"},"picture":{"large":"https://randomuser.me/api/portraits/men/68.jpg","medium":"https://randomuser.me/api/portraits/med/men/68.jpg","thumbnail":"https://randomuser.me/api/portraits/thumb/men/68.jpg"},"nat":"BR"}],"info":{"seed":"6f2443af3c512241","results":2,"page":1,"version":"1.4"}})";
    std::string mockResponse = R"({
  "results": [
    {
      "gender": "male",
      "name": { "title": "Mr", "first": "Kyoutarou", "last": "Ichikawa" },
      "location": {
        "street": { "number": 1, "name": "Library St" },
        "city": "Meguro", "state": "Tokyo", "country": "Japan", "postcode": 1530063,
        "coordinates": { "latitude": "35.6339", "longitude": "139.7081" },
        "timezone": { "offset": "+9:00", "description": "Tokyo" }
      },
      "email": "kyoutarou.ichikawa@example.com",
      "login": {
        "uuid": "550e8400-e29b-4d44-a716-446655440000",
        "username": "dark_knight_01", "password": "password123",
        "salt": "salt1", "md5": "md5_1", "sha1": "sha1_1", "sha256": "sha256_1"
      },
      "dob": { "date": "2008-03-26T00:00:00.000Z", "age": 16 },
      "registered": { "date": "2023-01-01T00:00:00.000Z", "age": 1 },
      "phone": "03-1234-5678", "cell": "090-1234-5678",
      "id": { "name": "STUDENT_ID", "value": "2024-001" },
      "picture": { "large": "https://example.com", "medium": "https://example.com", "thumbnail": "https://example.com" },
      "nat": "JP"
    },
    {
      "gender": "female",
      "name": { "title": "Miss", "first": "Anna", "last": "Yamada" },
      "location": {
        "street": { "number": 2, "name": "Snack Aisle Ave" },
        "city": "Meguro", "state": "Tokyo", "country": "Japan", "postcode": 1530063,
        "coordinates": { "latitude": "35.6339", "longitude": "139.7081" },
        "timezone": { "offset": "+9:00", "description": "Tokyo" }
      },
      "email": "anna.yamada@example.com",
      "login": {
        "uuid": "661f9511-f30c-5e55-b827-557766551111",
        "username": "sweets_queen", "password": "marshmallow",
        "salt": "salt2", "md5": "md5_2", "sha1": "sha1_2", "sha256": "sha256_2"
      },
      "dob": { "date": "2008-09-10T00:00:00.000Z", "age": 16 },
      "registered": { "date": "2023-02-01T00:00:00.000Z", "age": 1 },
      "phone": "03-8765-4321", "cell": "080-8765-4321",
      "id": { "name": "STUDENT_ID", "value": "2024-002" },
      "picture": { "large": "https://example.com", "medium": "https://example.com", "thumbnail": "https://example.com" },
      "nat": "JP"
    }
  ],
  "info": { "seed": "bokuyaba", "results": 2, "page": 1, "version": "1.4" }
})";

    EXPECT_CALL(*mock_client_,
                sendRequest(verb::get,
                            An<const std::string &>(),
                            _))
        .WillOnce(Return(mockResponse));

    // Act
    auto actual_response_ = sut_->FindAll(2);

    // Assert
    ASSERT_NE(actual_response_, std::nullopt);
    ASSERT_EQ(actual_response_->size(), 2);
}

} // namespace

} // namespace com_spudmash_cppuserapi::services
