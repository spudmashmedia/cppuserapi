# Build Instructions
## Local Build
Before beginning see prerequisites.

```
sh build.sh
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
