FROM gcc:15.2.0-trixie AS build

# 1 - Update base image
RUN apt-get update && apt-get install -y --no-install-recommends \
    curl \
    zip \
    unzip \
    tar \
    ca-certificates \
    cmake \
    && rm -rf /var/lib/apt/lists/*

# 2 - Setup Vcpkg
WORKDIR /usr
RUN git clone --depth 1 https://github.com/microsoft/vcpkg.git && ./vcpkg/bootstrap-vcpkg.sh

# 3 - Add environment variables
ENV VCPKG_HOME=/usr/vcpkg
ENV PATH=$VCPKG_HOME:$PATH

# 4 - Prep build directory and get vcpkg packages
WORKDIR /usr/cppuserapi
COPY vcpkg.json ./
RUN vcpkg install
COPY . .

# 5 - Build Project
RUN chmod +x build.sh && ./build.sh

# 6 - Run Unit Test
RUN ./build/CppUserApi_Tests

# Use this for small final size
FROM gcr.io/distroless/cc-debian13 AS app

# Use this for debugging
# FROM debian:trixie-slim AS app

WORKDIR /app
COPY --from=build /usr/cppuserapi/build/CppUserAPI .
COPY --from=build /usr/cppuserapi/cppuserapi_config.toml .
EXPOSE 3000
ENTRYPOINT ["./CppUserAPI"]
