# 2026-01-10
* Started work.
* Working on loading logs correctly.
* Logs are currently human-readable for easier debugging, but will eventually be made binary to improve performance.
* Added flushing while writing log file
* Added basic store using map

# 2026-01-18
* TCP server working
* `EXIT` command working
* Minor code improvements, with `const` guarantees

# 2026-01-22
* Write ahead logging improved; now saves to log properly
  * more improvements can be made
* Command parsing works for `EXIT`, `SET`, and `GET`
  * `DEL` needs work