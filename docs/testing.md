# Testing
## Test Scenarios

### Test: /Health should return response HTTP 200

#### Request
```
http get "http://localhost:3000/health"
```

#### Response
```
HTTP/1.1 200 OK
Connection: Keep-Alive
Content-Length: 51
Content-Type: application/json
Server: Crow/master
X-Correlation-Id: 0729457f-8dd7-4329-b1d3-8b48f33c3659

{
    "data": [
        null
    ],
    "error": {
        "code": 200,
        "message": "Ok"
    }
}
```

### Test: /user should return single result
#### Request
```
http get "http://localhost:3000/user"
```
#### Response
```
{"data":{"users":[{"address":"3253 Plum St, Rockhampton New South Wales 8740, Australia","email":"suzanne.peterson@example.com","name":"Mrs Suzanne Peterson"}]},"error":{"code":200,"message":"Ok"}}
```

### Test: /user?count=2 should return 2 results
NOTE: count has a range of 1-1000
#### Request
```
http get "http://localhost:3000/user?count=2"
```
#### Response
```
{"data":{"users":[{"address":"4093 York Road, Durham Somerset N85 4HG, United Kingdom","email":"tracey.miles@example.com","name":"Miss Tracey Miles"},{"address":"2344 Otavalankatu, Halsua Kymenlaakso 89099, Finland","email":"leevi.heikkila@example.com","name":"Mr Leevi Heikkila"}]},"error":{"code":200,"message":"Ok"}}
```

### Test: /user?count=-1 should return Bad Request
#### Request
```
http get "http://localhost:3000/user?count=-1"
```
#### Response
```
{"data":[null],"error":{"code":400,"message":"Value out of range. Got: -1"}}
```


### Test: /user?count=0 should return Bad Request
#### Request
```
http get "http://localhost:3000/user?count=0"
```
#### Response
```
{"data":[null],"error":{"code":400,"message":"Limit must be greater than zero (0). Got: 0"}}
```

### Test: /user?count=1001 should return Bad Request
#### Request
```
http get "http://localhost:3000/user?count=1001"
```
#### Response
```
{"data":[null],"error":{"code":400,"message":"Value out of range. Got: 1001"}}
```

### Test: /user/not/a/real/route should return Bad Request
#### Request
```
http get "http://localhost:3000/user/not/a/real/route"
```
#### Response
```
{"data":[null],"error":{"code":400,"message":"See logs for details."}}
```
