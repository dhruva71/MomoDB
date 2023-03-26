# MomoDB

A small in memory database for storing and retrieving data, built in Rust. Currently, this is in development, and should not be used in production.

## Future

- [ ] Add support for python (WIP)

## Notes

### Python bindings

They are currently in development, and are not ready for use. These exist in pymomodb, and are built using pyo3. To use:
1. Create a virtual environment, and install maturin.
2. Run `maturin develop` in the pymomodb directory.