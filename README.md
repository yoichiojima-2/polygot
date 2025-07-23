# polyglot

learn various languages by writing servers in them, without LLM help because the main purpose is learning them


## Server Specification

This document defines the common server requirements that all language implementations must follow.

### Overview

Each server implementation should be a simple HTTP server that demonstrates core language features and best practices.

### Core Requirements

#### 1. Server Configuration
- **Port**: 8080 (configurable via environment variable `PORT`)
- **Host**: localhost/127.0.0.1
- **Protocol**: HTTP/1.1

#### 2. Required Endpoints

##### GET /
- **Description**: Health check endpoint
- **Response**: 
  ```json
  {
    "status": "ok",
    "language": "<language_name>",
    "version": "<language_version>"
  }
  ```
- **Status Code**: 200

##### GET /echo/:message
- **Description**: Echo the message parameter
- **Response**: 
  ```json
  {
    "echo": "<message>",
    "timestamp": "<ISO-8601 timestamp>"
  }
  ```
- **Status Code**: 200

##### POST /json
- **Description**: Accept JSON body and return processed data
- **Request Body**: 
  ```json
  {
    "data": "any valid JSON"
  }
  ```
- **Response**: 
  ```json
  {
    "received": "<request_body>",
    "processed_at": "<ISO-8601 timestamp>",
    "size": <bytes>
  }
  ```
- **Status Code**: 200

##### GET /fibonacci/:n
- **Description**: Calculate nth Fibonacci number
- **Constraints**: n must be between 0 and 92
- **Response**: 
  ```json
  {
    "n": <n>,
    "result": <fibonacci_number>,
    "calculation_time_ms": <time>
  }
  ```
- **Status Code**: 200 (valid n), 400 (invalid n)

##### GET /stats
- **Description**: Server statistics
- **Response**: 
  ```json
  {
    "uptime_seconds": <seconds>,
    "requests_handled": <count>,
    "memory_usage_mb": <mb>,
    "start_time": "<ISO-8601 timestamp>"
  }
  ```
- **Status Code**: 200

#### 3. Error Handling

All errors should return consistent JSON responses:
```json
{
  "error": "<error_message>",
  "path": "<request_path>",
  "timestamp": "<ISO-8601 timestamp>"
}
```

Status codes:
- 400: Bad Request (invalid parameters)
- 404: Not Found (unknown endpoint)
- 405: Method Not Allowed
- 500: Internal Server Error

#### 4. Logging

Each server should log:
- Server start/stop events
- Incoming requests: `[timestamp] METHOD path - status_code (duration_ms)`
- Errors with stack traces

#### 5. Graceful Shutdown

- Handle SIGINT/SIGTERM signals
- Complete in-flight requests
- Log shutdown event

### Implementation Guidelines

#### Code Structure
Each language implementation should have:
```
<language>/
├── README.md          # Language-specific setup and run instructions
├── main.<ext>         # Entry point
├── server.<ext>       # Server implementation
├── handlers.<ext>     # Request handlers
└── <build_file>       # Language-specific build/dependency file
```

#### Testing
- Unit tests for handlers
- Integration tests for endpoints
- Performance benchmarks for Fibonacci calculation

#### Documentation
Each implementation must include:
- Setup instructions
- Dependencies list
- Language-specific design decisions
- Performance characteristics

### Performance Targets
- Startup time: < 1 second
- Simple endpoint response time: < 10ms
- Fibonacci(50) calculation: < 100ms
- Memory usage: < 100MB under normal load

### Security Considerations
- No file system access outside project directory
- Input validation on all endpoints
- No execution of user-provided code
- Rate limiting (optional but recommended)
