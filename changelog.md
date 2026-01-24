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

# 2026-01-23
* Fixed a bug with map insertion
  * should've used `insert_or_assign`, instead of `insert`
* Renamed `Put` to `Set` for better uniformity
* Improved insertion return logic
* Improved deletion logic
* Improved log writing
  * now it actually works like a streaming WAL
* Fix logic for rebuilding from log
* Store functions now support a boolean flag on whether they should write to log or not
* Improved flushing WAL to disk
* Improved logging to indicate when keystore was actually rebuilt from WAL

# 2026-01-24
* Switched from `map` to `unordered_map`
  * Average time complexity of `map` is O(log n), whearas `unordered_map` is O(1)
  * Worst case performance of `unordered_map` is O(n)
  * `unordered_map` does take more memory than `map`
  * Better comparision [here at Stack Overflow](https://stackoverflow.com/questions/2196995/is-there-any-advantage-of-using-map-over-unordered-map-in-case-of-trivial-keys)