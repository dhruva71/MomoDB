# MomoDB
**Work in progress**

![Logo created using Nano Banana](logo.png)

* A **key-value store**, created purely for educational purposes.
* Built in C++. This is making use of C++20 features, so you will need a modern compiler to build this.
* Named after [Momo (Wikipedia)](https://en.wikipedia.org/wiki/Momo_(food))

## Commands
* `SET <key> <value>`: holds value `<value>` against key `<key>`
* `GET <key>`: returns value 
* `DEL <key>`: deletes a key; essentially marks it as <deleted>

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
  * `DEL` works by overwriting the value with an empty string.
  * Can be tested locally using `nc localhost 9001`

### Performance
* Current performance (based on a toy script acting as a client) in a single thread, with connections being closed after every request (debug build):
```text
Successfully completed: 10000/10000
Total time: 1.07 seconds
Performance: 9347.80 operations/sec
```
* Switching to release build gives (note the switch to 100k operations; it should not matter much since we are primarily comparing operations/sec):
```text
Successfully completed: 100000/100000
Total time: 8.73 seconds
Performance: 11458.47 operations/sec
```
* In single-client persistent client mode i.e a client connects and stays connected, we get (please note that the number of operations has been increased to 100K, but it should not matter much) (debug build):
```text
Successfully completed: 100000/100000
Total time: 3.66 seconds
Performance: 27290.68 operations/sec
```
* Switching to release build + persistent single client mode gives:
```text
Successfully completed: 100000/100000
Total time: 2.72 seconds
Performance: 36751.67 operations/sec
```
* Switching to release build + jemalloc + persistent single client mode gives:
```text
Successfully completed: 100000/100000
Total time: 2.63 seconds
Performance: 38078.49 operations/sec
```
* Release build + jemalloc + no logging + persistent single client mode gives:
```text
Successfully completed: 100000/100000
Total time: 2.07 seconds
Performance: 48425.44 operations/sec
```
* Release build + jemalloc + no logging + stdout disabled + persistent client mode gives:
```text
Successfully completed: 100000/100000
Total time: 1.79 seconds
Performance: 55745.68 operations/sec
```
* Release build (O3) + jemalloc + no logging + stdout disabled + persistent single client mode gives:
```text
Successfully completed: 100000/100000
Total time: 1.66 seconds
Performance: 60321.11 operations/sec
```

## TODOs
* Performance improvements can be made to a lot of aspects.
* Large scale tests are pending.
* Unit tests are pending.
* Better data structures and writing methods.
* Better network protocol is needed.

## Known issues
* JSON values cause issues, since they have a `:`
  * switching to a newer format is required.
* Server closes TCP connection after every request.
  * This reduces the potential speed it can reach as TCP handshake has to be repeated.
  * Switching to epoll or io_uring is the potential next step.

## What I'll look into next
* Improving networking
  * persistent connections and handling multiple clients properly
* Improving log format
  * Currently hitting limits
* Improving internal data structures.
  * `map` was a good start, but better data structures exist.
  * Switched to using `unordered_map` currently

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