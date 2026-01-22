# MomoDB
**WIP**

![Logo created using Nano Banana](logo.png)

A key-value store, created purely for educational purposes.
Built in C++. This is making use of C++20 features, so you will need a modern compiler to build this. It also uses CMake
build system.

## Current capabilities
* Reading and writing to log files successfully.
* Storage using map.
* Rebuilding map based on log file.
* Added basic TCP server
  * Listens to port 9001 (hardcoded currently)
    * You can find processes using 9001 already using `sudo ss -tulnp | grep :9001`
  * Currently, can accept commands and responds with `OK`
  * `EXIT` command works to shut down the server
  * `SET`, `GET` work
  * `DEL` has an issue
  * Can be tested locally using `nc localhost 9001`
* Performance improvements can be made to a lot of aspects.
* Large scale tests are pending.

## Log format
For human readability and easier debugging, logs are plain-text only for now. They will be moved to a binary format once
features are more stable.

Currently log format is:
```text
timestamp:operation_type:key:value
```

Example:
```text
1768059728273357375:1:userid:42
```
This has clear flaws, for example, keys and values cannot contain `:` themselves or everything breaks down, but this is
a decent enough start for a system.

## AI usage
0 or minimal AI code will be involved, as it is more of a learning exercise pursuing newer C++ features and performance.

## Pull requests
Currently not accepting any.