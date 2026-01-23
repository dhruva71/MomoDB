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

## TODOs
* Performance improvements can be made to a lot of aspects.
* Large scale tests are pending.
* Unit tests are pending.
* Better data structures and writing methods.
* Better network protocol is needed.

## Known issues
* JSON values cause issues, since they have a `:`
  * switching to a newer format is required

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