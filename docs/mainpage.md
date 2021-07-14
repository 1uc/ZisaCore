# ZisaCore                                                           {#mainpage}
ZisaCore is a minimal collection of functionality without which the other
libraries can't be written. Most notably it includes logging, file and string
related functions. As well as abstractions for the CUDA related function
decorations (`__device__` and friends). In and of itself it is of little
interest to anyone.

## Quickstart
Start by installing the dependencies by running

    $ bin/install_dir.sh COMPILER DIRECTORY

which will install the dependencies into a subfolder of `DIRECTORY` and print
part of the CMake command needed to include the dependencies. `COMPILER` must
be replaced with the compiler you want to use.

If this worked continue by adding [project specific flags] to the CMake
command. If not it's not going to be a quick start. Please read
[Dependencies] and then [Building].

[project specific flags]: @ref cmake_flags
[Dependencies]: dependencies.md
[Building]: cmake.md
