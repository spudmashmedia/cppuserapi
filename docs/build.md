# Build Instructions
## Local Build
Before beginning see prerequisites.

### Build API (on port 3000)
```
sh build.sh
```

### Run API

```
./build/CppUserAPI
```


## Docker

### Build Image
```
docker build -t cppuserapi .
```

### Run Image In Container
```
docker run -d -it --name cppuserapi_test -p 3000:3000 cppuserapi
```

### Health Check
With Httpie (or Postman)
```
http get "http://localhost:3000/health"
```

### Configuration
see [cppuserapi_config.toml](../cppuserapi_config.toml)

```
[server]
concurrency = 4
port = 3000

[services]
randomuser_limit = 1000
randomuser_host = "randomuser.me"
randomuser_port = "443"
randomuser_path_api = "/api"
```

#### Server.conconurrency (default 4)
Increase this to the number of available cores - 4 is the sweet spot for M1 Max

#### Server.port (default 3000)
Host port - remember to update the Dockerfile exposed port if this changes (see [Dockerfile](../Dockerfile))

#### Services.randomuser_host (default user service host)
Defaulted to randomuser.me

#### Services.randomuser_port (default user service port)
public website is using TLS 443

#### Services.randomuser_limit (default user service retrieval limit)
Current max limit is 1000 retrieval. Affects the query string parameter "count".
e.g http://localhost:3000/user?count=1000

#### Services.randomuser_path_api (default user service )
this is the default route for randomuser.me
e.g. https://randomuser.me/api

