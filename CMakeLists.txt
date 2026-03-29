#------------------------------------------------------------------
#  Copyright (c) Spudmash Media Pty Ltd. All rights reserved.
#  Licensed under the MIT License.
#  See License.txt in the project root for license information.
#------------------------------------------------------------------

#
# Main Build Binary
# 
cmake_minimum_required(VERSION 3.15)

if(POLICY CMP0167)
  cmake_policy(SET CMP0167 OLD)
endif()

project(CppUserAPI CXX)

set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# set(CMAKE_TOOLCHAIN_FILE $VCPKG_HOME/scripts/buildsystems/vcpkg.cmake)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

list(APPEND CMAKE_PREFIX_PATH "/opt/homebrew")
find_package(Crow CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(Boost CONFIG REQUIRED COMPONENTS system uuid)
find_package(OpenSSL REQUIRED)
find_package(Threads REQUIRED)
find_package(tomlplusplus CONFIG REQUIRED)

set(APP_LOGIC_SOURCES
  src/api/api.cpp
  include/utils/config/config.hpp
  include/utils/config/config_options.h
  include/utils/config/api_options.h
  include/utils/config/user_service_options.h
  include/utils/logger/app_logger.hpp

  include/controllers/controller.h
  include/controllers/base_controller.hpp
  src/controllers/catch_all_controller.cpp
  src/controllers/user_controller.cpp
  src/controllers/health_controller.cpp

  include/services/base_service.hpp
  include/services/user_service.h
  src/services/user_service.cpp

  include/utils/http/http_client.hpp
  include/utils/http/boost_http_client.h
  src/utils/http/boost_http_client.cpp
  include/middleware/correlation_id_middleware.hpp

  include/dtos/json_response_base.hpp
  include/dtos/user_response.hpp
  include/dtos/health_response.hpp

  include/dtos/mappers/user_response_mapper.hpp

  include/models/gps_location.hpp
  include/models/identifier.hpp
  include/models/image_set.hpp
  include/models/location.hpp
  include/models/login.hpp
  include/models/name.hpp
  include/models/street.hpp
  include/models/time_alive.hpp
  include/models/timezone.hpp
  include/models/user.hpp
)

# Create app_logic target
add_library(app_logic STATIC ${APP_LOGIC_SOURCES})

# Target directories
target_include_directories(app_logic PUBLIC
  "${CMAKE_CURRENT_SOURCE_DIR}/src"
  "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

# Link with Crow Library
target_link_libraries(
  app_logic PUBLIC
  Crow::Crow
  asio::asio
  nlohmann_json::nlohmann_json
  Boost::boost
  Boost::system
  OpenSSL::SSL
  OpenSSL::Crypto
  Threads::Threads
  tomlplusplus::tomlplusplus
)

add_executable(CppUserAPI src/main.cpp)
target_link_libraries(CppUserAPI PRIVATE app_logic)


#
# Test Binary  - reuse app_logic for testing
# 
option(BUILD_TESTS "Build unit tests" ON)

if(BUILD_TESTS)
  enable_testing()
  find_package(GTest CONFIG REQUIRED)

  add_executable(CppUserApi_Tests
    tests/main.cpp
    tests/services/user_service_test.cpp
  )

  target_link_libraries(CppUserApi_Tests PRIVATE
    app_logic
    GTest::gtest_main
    GTest::gmock
  )

  target_include_directories(CppUserApi_Tests PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/tests"
  )
endif()
