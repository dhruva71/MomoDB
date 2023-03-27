# MomoDB

A small in memory database for storing and retrieving data, built in Rust. Currently, this is in development, and should not be used in production.

## Future

- [x] Add support for python (WIP)
- [ ] Add time based data expiration

## Notes

### Python bindings

They are currently in development, and are not ready for use. These exist in pymomodb, and are built using pyo3. To use:
1. Create a virtual environment, and install maturin.
2. Run `maturin develop` in the pymomodb directory to install the python bindings in your virtual environment.
3. Run `maturin build` to build the python bindings inside `target/wheels`, and not installing them right away.
   1. If you have issues with this command finding python, use `maturin build --release -i python`.