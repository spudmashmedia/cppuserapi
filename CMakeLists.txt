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
find_package(Boost REQUIRED COMPONENTS system uuid)
find_package(OpenSSL REQUIRED)
find_package(Threads REQUIRED)
find_package(tomlplusplus CONFIG REQUIRED)

set(SOURCE_FILES
  src/main.cpp
  src/api/api.cpp
  include/utils/config/config.hpp
  include/utils/config/config_response.hpp
  include/utils/logger/app_logger.hpp

  src/controllers/catch_all_controller.cpp
  src/controllers/user_controller.cpp
  src/controllers/health_controller.cpp

  src/services/user_service.cpp

  src/utils/http/http_client.cpp
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

# Executable
add_executable(CppUserAPI ${SOURCE_FILES})

# Target directories
target_include_directories(CppUserAPI PRIVATE
  ${Boost_INCLUDE_DIRS}
  "${CMAKE_CURRENT_SOURCE_DIR}/src"
  "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

# Link with Crow Library
target_link_libraries(
  CppUserAPI PRIVATE
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
