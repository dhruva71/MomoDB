from setuptools import setup
from setuptools_rust import Binding, RustExtension

setup(
    name="pymomodb",
    version="0.1.0",
    rust_extensions=[
        RustExtension("pymomodb", "Cargo.toml", binding=Binding.PyO3)
    ],
    packages=["pymomodb"],
    zip_safe=False,
)
