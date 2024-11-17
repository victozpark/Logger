# Logger
Simple and high-performance log module based on C/C++

## Basic features are as follows 
- Prints log to standard output.
- Prints log to the specified log file.
- Filter logs based on log levels.

## Also you can
- Change log format through inheritance.
- Use threaded Logger for high performance (but some log can be lost when Queue is full)

## UML class diagram
#### Logger module
<img src="https://private-user-images.githubusercontent.com/46546765/386926311-2c73f266-97a0-4222-b034-40081d6479d3.png?jwt=eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpc3MiOiJnaXRodWIuY29tIiwiYXVkIjoicmF3LmdpdGh1YnVzZXJjb250ZW50LmNvbSIsImtleSI6ImtleTUiLCJleHAiOjE3MzE4ODA3NjksIm5iZiI6MTczMTg4MDQ2OSwicGF0aCI6Ii80NjU0Njc2NS8zODY5MjYzMTEtMmM3M2YyNjYtOTdhMC00MjIyLWIwMzQtNDAwODFkNjQ3OWQzLnBuZz9YLUFtei1BbGdvcml0aG09QVdTNC1ITUFDLVNIQTI1NiZYLUFtei1DcmVkZW50aWFsPUFLSUFWQ09EWUxTQTUzUFFLNFpBJTJGMjAyNDExMTclMkZ1cy1lYXN0LTElMkZzMyUyRmF3czRfcmVxdWVzdCZYLUFtei1EYXRlPTIwMjQxMTE3VDIxNTQyOVomWC1BbXotRXhwaXJlcz0zMDAmWC1BbXotU2lnbmF0dXJlPTA3MTgxZjE2MWNjOWMzMjc1MmZmMzFiODU0NWM5OTU0NGMwMDQ4NDk1MmI2ZTVmYjQ5Mzg5M2JhMmM0NjY4MGImWC1BbXotU2lnbmVkSGVhZGVycz1ob3N0In0.ITSwypRY6xl49knnz4lo7faeuF_ZzFVIf0WPJR_SM6g" width="60%">

----

## Install (Logger module)
```shell
$ mkdir build                # Make a build directory
$ cd build                   # Change to the build directory
$ cmake ..                   # Create a Makefile
$ make                       # Make a libray file
$ make install               # Install header and library files
$ ls -al ../release/include  # You can check a header file
$ ls -al ../release/lib      # You can check a library file
```

## Test 
```shell
### "Install" is required before testing.
$ cd test                    # Change to the test directory
$ mkdir build                # Make a build directory
$ cd build                   # Change to the build directory
$ cmake ..                   # Create a Makefile
$ make                       # Make a binary file
$ ./main                     # Run test
```
----
## Examples
### SimpleLogger
- Simple logger.
```c++
//
// Set namespace
//
using namespace vp;

//
// Define log macros
//
#define LOG_TRC(...)  _LOG_TRC(logger, __VA_ARGS__)
#define LOG_DBG(...)  _LOG_DBG(logger, __VA_ARGS__)
#define LOG_INFO(...) _LOG_INFO(logger, __VA_ARGS__)
#define LOG_WARN(...) _LOG_WARN(logger, __VA_ARGS__)
#define LOG_ERR(...)  _LOG_ERR(logger, __VA_ARGS__)

SimpleLogger logger;

//
// Bassic logger settings
//
{
  ALogger &abst = logger;
  abst.setFilePath("."); // Set the log file path
  abst.setFileName("test.log"); // Set the log file name
  abst.setMaxLogLength(4096); // Set the maximum log length
  abst.setLogStdoutEnabled(true); // Enable printing log to standard output
  abst.setLogLevel(LogLevel::LOG_LEVEL_ALL); // LogLevel::LOG_LEVEL_ALL for all Log Levels.
      // You can set multiple log levels using the logical operation "|".
      // For example, if you set Log level as LogLevel::LOG_LEVEL_WARNING | LogLevel::LOG_LEVEL_ERROR,
      // only “Error” and “Warning” will be printed.
}

//
// Initialize the logger
//
if (logger.initialize() != RetType::RET_SUCCESS) {
  fprintf(stderr, "Failed to initialize logger\n");
  return -1;
}

LOG_TRC( "Hello world!! [T]");
LOG_DBG( "Hello world!! [D]");
LOG_INFO("Hello world!! [I]");
LOG_WARN("Hello world!! [W]");
LOG_ERR( "Hello world!! [E]");

//
// Finalize the logger
//
if (logger.finalize() != RetType::RET_SUCCESS) {
  fprintf(stderr, "Failed to finalize logger\n");
  return -1;
}
```

### ThreadedLogger
- Threaded logger. (***High-performance***)
- A logger thread will be created. And in this thread, log will be written in a log file.
```c++
//
// Set namespace
//
using namespace vp;

//
// Define log macros
//
#define LOG_TRC(...)  _LOG_TRC(logger, __VA_ARGS__)
#define LOG_DBG(...)  _LOG_DBG(logger, __VA_ARGS__)
#define LOG_INFO(...) _LOG_INFO(logger, __VA_ARGS__)
#define LOG_WARN(...) _LOG_WARN(logger, __VA_ARGS__)
#define LOG_ERR(...)  _LOG_ERR(logger, __VA_ARGS__)

ThreadedLogger logger;

//
// Bassic logger settings
//
{
  ALogger &abst = logger;
  abst.setFilePath("."); // Set the log file path
  abst.setFileName("test.log"); // Set the log file name
  abst.setMaxLogLength(4096); // Set the maximum log length
  abst.setLogStdoutEnabled(true); // Enable printing log to standard output
  abst.setLogLevel(LogLevel::LOG_LEVEL_ALL); // LogLevel::LOG_LEVEL_ALL for all Log Levels.
      // You can set multiple log levels using the logical operation "|".
      // For example, if you set Log level as LogLevel::LOG_LEVEL_WARNING | LogLevel::LOG_LEVEL_ERROR,
      // only “Error” and “Warning” will be printed.
}

//
// Threaded logger settings
//
{
  logger.setMaxQueueSize(8192); // Set the maximum queue size (Default 4096)
  logger.setPollingSleepUs(1); // Set the polling sleep time in micro seconds (0 means no sleep but polling, Default 1000)
}

//
// Initialize the logger
//
if (logger.initialize() != RetType::RET_SUCCESS) {
  fprintf(stderr, "Failed to initialize logger\n");
  return -1;
}

//
// Print log
//
LOG_TRC( "Hello world!! [T]");
LOG_DBG( "Hello world!! [D]");
LOG_INFO("Hello world!! [I]");
LOG_WARN("Hello world!! [W]");
LOG_ERR( "Hello world!! [E]");

//
// Finalize the logger
//
if (logger.finalize() != RetType::RET_SUCCESS) {
  fprintf(stderr, "Failed to finalize logger\n");
  return -1;
}
```

### SimpleLogger with a user log formatter
- Users can set their own log format
```c++
//
// Set namespace
//
using namespace vp;

//
// Define log macros
//
#define LOG_TRC(...)  _LOG_TRC(logger, __VA_ARGS__)
#define LOG_DBG(...)  _LOG_DBG(logger, __VA_ARGS__)
#define LOG_INFO(...) _LOG_INFO(logger, __VA_ARGS__)
#define LOG_WARN(...) _LOG_WARN(logger, __VA_ARGS__)
#define LOG_ERR(...)  _LOG_ERR(logger, __VA_ARGS__)

//
// User log formatter class
//
class UserLogFormatter : public ILogFormatter
{
public:
  UserLogFormatter() = default;
  virtual ~UserLogFormatter() = default;
  virtual auto format(char *pzLogBuffer, int nLogBufferLength,
            LogLevel eLogLevel, const char *pzFileName, const char *pzFunctionName, int nLine,
            const char *pzFormat, va_list &vaList) -> int
  {
    int nLength = 0;
    nLength = snprintf(pzLogBuffer, nLogBufferLength, "[%02ld] [%s:%d] [%s] ", eLogLevel, pzFileName, nLine, pzFunctionName);
    nLength += vsnprintf(pzLogBuffer + nLength, nLogBufferLength - nLength, pzFormat, vaList);
    return nLength;
  }
};

SimpleLogger logger;
UserLogFormatter fomatter;

//
// Bassic logger settings
//
{
  ALogger &abst = logger;
  abst.setFilePath("."); // Set the log file path
  abst.setFileName("test.log"); // Set the log file name
  abst.setMaxLogLength(4096); // Set the maximum log length
  abst.setLogStdoutEnabled(true); // Enable printing log to standard output
  abst.setLogLevel(LogLevel::LOG_LEVEL_ALL); // LogLevel::LOG_LEVEL_ALL for all Log Levels.
      // You can set multiple log levels using the logical operation "|".
      // For example, if you set Log level as LogLevel::LOG_LEVEL_WARNING | LogLevel::LOG_LEVEL_ERROR,
      // only “Error” and “Warning” will be printed.
  abst.setLogFormatter(&fomatter); // Set a user log formatter
}

//
// Initialize the logger
//
if (logger.initialize() != RetType::RET_SUCCESS) {
  fprintf(stderr, "Failed to initialize logger\n");
  return -1;
}

//
// Print log
//
LOG_TRC( "Hello world!! [T]");
LOG_DBG( "Hello world!! [D]");
LOG_INFO("Hello world!! [I]");
LOG_WARN("Hello world!! [W]");
LOG_ERR( "Hello world!! [E]");

//
// Finalize the logger
//
if (logger.finalize() != RetType::RET_SUCCESS) {
  fprintf(stderr, "Failed to finalize logger\n");
  return -1;
}
```
----
Please let me know if there are any bugs or features you would like to use. <br>
Thank you. :)
