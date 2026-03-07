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

find_package(Crow CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(Boost REQUIRED COMPONENTS system)
find_package(OpenSSL REQUIRED)
find_package(Threads REQUIRED)

include(FetchContent)
FetchContent_Declare(
    tomlplusplus
    GIT_REPOSITORY https://github.com/marzer/tomlplusplus.git
    GIT_TAG        v3.4.0
)
FetchContent_MakeAvailable(tomlplusplus)

include_directories(
  "src/"
  "include/"
)

set(SOURCE_FILES
  src/main.cpp
  src/api/api.cpp
  include/utils/config/config.hpp
  include/utils/config/config_response.hpp

  src/controllers/user_controller.cpp
  src/services/user_service.cpp

  src/utils/http/http_client.cpp

  src/controllers/health_controller.cpp

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
)
