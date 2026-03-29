/*--------------------------------------------------------------------
 *  Copyright (c) Spudmash Media Pty Ltd. All rights reserved.
 *  Licensed under the MIT License.
 *  See License.txt in the project root for license information.
 *------------------------------------------------------------------*/

#include "mocks/user_data_mocks.hpp"
#include "mocks/utils/http/mock_http_client.hpp"
#include "models/user.hpp"
#include "services/user_service.h"
#include "utils/config/user_service_options.h"

#include <boost/beast/http.hpp>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <stdexcept>

namespace com_spudmash_cppuserapi::services
{
namespace
{

using boost::beast::http::verb;
using com_spudmash_cppuserapi::tests::mocks::UserDataMocks;
using ::testing::_;
using ::testing::An;
using ::testing::Return;
using ::testing::Throw;

class UserServiceTest : public ::testing::Test
{
  protected:
    utils::config::UserServiceOptions mock_cfg_;
    std::shared_ptr<utils::http::MockHttpClient> mock_client_;
    std::shared_ptr<services::UserService> sut_;

    void SetUp()
    {
        mock_client_ = std::make_shared<utils::http::MockHttpClient>();
        sut_ = std::make_shared<services::UserService>(mock_cfg_, mock_client_);
    }
};

void ValidateUser(const nlohmann::json &expected,
                  const models::User &actual)
{
    ASSERT_EQ(expected["name"]["title"],
              actual.name.title);

    ASSERT_EQ(expected["name"]["title"],
              actual.name.title);

    ASSERT_EQ(expected["name"]["first"],
              actual.name.first);

    ASSERT_EQ(expected["name"]["last"],
              actual.name.last);

    ASSERT_EQ(expected["gender"],
              actual.gender);

    ASSERT_EQ(expected["location"]["street"]["number"],
              actual.location.street.number);

    ASSERT_EQ(expected["location"]["street"]["name"],
              actual.location.street.name);

    ASSERT_EQ(expected["location"]["city"],
              actual.location.city);

    ASSERT_EQ(expected["location"]["state"],
              actual.location.state);

    ASSERT_EQ(expected["location"]["country"],
              actual.location.country);

    ASSERT_EQ(std::format("{}", expected["location"]["postcode"].dump()),
              actual.location.postcode);

    ASSERT_EQ(expected["location"]["coordinates"]["latitude"],
              actual.location.coordinates.latitude);

    ASSERT_EQ(expected["location"]["coordinates"]["longitude"],
              actual.location.coordinates.longitude);

    ASSERT_EQ(expected["location"]["timezone"]["description"],
              actual.location.timezone.description);

    ASSERT_EQ(expected["location"]["timezone"]["offset"],
              actual.location.timezone.offset);

    ASSERT_EQ(expected["email"],
              actual.email);

    ASSERT_EQ(expected["login"]["uuid"],
              actual.login.uuid);

    ASSERT_EQ(expected["login"]["username"],
              actual.login.username);

    ASSERT_EQ(expected["login"]["password"],
              actual.login.password);

    ASSERT_EQ(expected["login"]["salt"],
              actual.login.salt);

    ASSERT_EQ(expected["login"]["md5"],
              actual.login.md5);

    ASSERT_EQ(expected["login"]["sha1"],
              actual.login.sha1);

    ASSERT_EQ(expected["login"]["sha256"],
              actual.login.sha256);

    ASSERT_EQ(expected["dob"],
              actual.dob);

    ASSERT_EQ(expected["registered"]["date"],
              actual.registered.date);

    ASSERT_EQ(expected["registered"]["age"],
              actual.registered.age);

    ASSERT_EQ(expected["phone"],
              actual.phone);

    ASSERT_EQ(expected["cell"],
              actual.cell);

    ASSERT_EQ(expected["id"]["name"],
              actual.id.name);

    ASSERT_EQ(expected["id"]["value"],
              actual.id.value);

    ASSERT_EQ(expected["picture"]["large"],
              actual.picture.large);

    ASSERT_EQ(expected["picture"]["medium"],
              actual.picture.medium);

    ASSERT_EQ(expected["picture"]["thumbnail"],
              actual.picture.thumbnail);

    ASSERT_EQ(expected["nat"],
              actual.nat);
}

TEST_F(UserServiceTest, FindAll_2_Should_Return_2_Users)
{
    // Arrange
    auto test_data_ = UserDataMocks::GenerateData(2);
    int test_count_ = 2;

    EXPECT_CALL(*mock_client_,
                sendRequest(verb::get,
                            An<const std::string &>(),
                            _))
        .WillOnce(Return(test_data_.dump()));

    // Act
    std::optional<std::vector<models::User>> actual_response_ =
        sut_->FindAll(test_count_);

    // Assert
    ASSERT_NE(actual_response_, std::nullopt);
    ASSERT_EQ(actual_response_->size(), test_count_);

    for (auto i = 0; i < actual_response_->size(); i++)
    {
        ValidateUser(test_data_["results"][i], actual_response_->at(i));
    }
}

TEST_F(UserServiceTest, FindAll_When_Limit_Is_Zero_Should_Throw_InvalidArgumentException)
{
    // Arrange
    auto test_data_ = UserDataMocks::GenerateData(0);
    const std::string expected_msg_ = "Limit must be greater than zero (0). Got: 0";

    // Act
    // Assert
    EXPECT_THROW({
          try {
            sut_->FindAll(0);
            }
          catch(std::invalid_argument ex){
            ASSERT_EQ(expected_msg_, ex.what());
            throw;
          } }, std::invalid_argument);
}

TEST_F(UserServiceTest, FindAll_When_No_Results_Return_Nullopt)
{
    // Arrange
    auto test_data_ = UserDataMocks::GenerateData(1);

    EXPECT_CALL(*mock_client_,
                sendRequest(verb::get,
                            An<const std::string &>(),
                            _))
        .WillOnce(Return(UserDataMocks::USER_RESULTS_ZERO_.dump()));

    // Act
    std::optional<std::vector<models::User>> actual_response_ =
        sut_->FindAll(1);

    // Assert
    ASSERT_EQ(actual_response_, std::nullopt);
}

TEST_F(UserServiceTest, FindAll_When_HttpClient_ThrowsException_Should_Return_Nullopt)
{
    // Arrange
    EXPECT_CALL(*mock_client_,
                sendRequest(verb::get,
                            An<const std::string &>(),
                            _))
        .WillOnce(Return(UserDataMocks::BAD_JSON_.dump()));

    // Act
    std::optional<std::vector<models::User>> actual_response_ =
        sut_->FindAll(1);

    // Assert
    ASSERT_EQ(actual_response_, std::nullopt);
}

TEST_F(UserServiceTest, First_Should_Return_User)
{
    // Arrange
    auto test_data_ = UserDataMocks::GenerateData(1);

    EXPECT_CALL(*mock_client_,
                sendRequest(verb::get,
                            An<const std::string &>(),
                            _))
        .WillOnce(Return(test_data_.dump()));

    // Act
    std::optional<models::User> actual_response_ =
        sut_->First();

    // Assert
    ASSERT_NE(actual_response_, std::nullopt);
    ValidateUser(test_data_["results"][0], actual_response_.value());
}

TEST_F(UserServiceTest, First_When_No_Results_Return_Nullopt)
{
    // Arrange
    auto test_data_ = UserDataMocks::GenerateData(1);

    EXPECT_CALL(*mock_client_,
                sendRequest(verb::get,
                            An<const std::string &>(),
                            _))
        .WillOnce(Return(UserDataMocks::USER_RESULTS_ZERO_.dump()));

    // Act
    std::optional<models::User> actual_response_ =
        sut_->First();

    // Assert
    ASSERT_EQ(actual_response_, std::nullopt);
}

TEST_F(UserServiceTest, First_When_HttpClient_ThrowsException_Should_Return_Nullopt)
{
    // Arrange
    EXPECT_CALL(*mock_client_,
                sendRequest(verb::get,
                            An<const std::string &>(),
                            _))
        .WillOnce(Return(UserDataMocks::BAD_JSON_.dump()));

    // Act
    std::optional<models::User> actual_response_ =
        sut_->First();

    // Assert
    ASSERT_EQ(actual_response_, std::nullopt);
}

} // namespace

} // namespace com_spudmash_cppuserapi::services

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
