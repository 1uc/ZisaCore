# Dependencies
## Automated dependencies
Naturally, while it can be useful to be able to install each of the
dependencies manually, e.g., on a pesky cluster, for the most part this can be
automated in a script.

To install the dependencies use

    $ bin/install_dir.sh COMPILER DIRECTORY

which will install the dependencies into a subfolder of `DIRECTORY` and print
part of the CMake command needed to include the dependencies. `COMPILER` must
be replaced with the compiler you want to use.

If this worked continue by adding [project specific flags]

[project specific flags]: cmake.md#cmake_flags

## Overview of dependencies
Zisa uses modern CMake to manage any dependencies it has. We've devided them
into four categories: *system dependencies* which are hard to install, low
level libraries; *common dependencies* these are properly packaged libraries;
*internal dependencies* meaning other parts of Zisa; and finally *scientific
dependencies* these are dependencies on other scientific codes, which may not
be nicely packaged and might not be open-source.

### System dependencies
We simply assume that these are present on the system. On a personal computer
these are intalled using the package manager or something similar.

Examples are:
  * CUDA
  * MPI
  * HDF5
  * NetCDF


### Common dependencies
Since these are nicely packaged C++ libraries, we can use Conan to install
them. Conan can be installed using `pip`, e.g.,

    pip install --user conan

Remember that you might need to add a folder to your `PATH`. There is a
`conanfile.txt` which lists the libraries that need to be installed.

**Note:** If you're new to Conan and it's using the correct compiler, please read
up on profiles. Which is how you can tell Conan the details required to pick an
ABI compatible binary.

Please refer to [Conan Details] for further details on how we use Conan.

[Conan Details]: conan.md

### Internal dependencies
These are distributed as source. Hence one must clone or download the
repository; then compile and install using typical CMake commands. Once they're
installed they are no different from common dependencies.

### Scientific dependencies
These are installed using custom scripts, check `bin/` for anything with a
related name. Note, that these dependencies are always optional, and not present
in all parts of Zisa.

