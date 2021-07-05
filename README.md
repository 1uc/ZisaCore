# ZisaCore
ZisaCore is a minimal collection of functionality without which the other
libraries can't be written. Most notably it includes logging, file and string
related functions. As well as abstractions for the CUDA related function
decorations (`__device__` and friends). In and of itself it is of little
interest to anyone.

## Dependencies
We do not attempt to install either CUDA or MPI. If either is needed we simply
assume that they are present and can be found by CMake.

We use Conan to install some of the simpler dependencies locally. Please ensure
that `conan` is present in the `PATH`. On Linux, the recommended way to install
Conan is

    $ pip install --user conan

## Installing
The remaining dependencies are installed by

    $ bin/install_dir.sh COMPILER DIRECTORY

which will install the dependencies into a subfolder of `DIRECTORY` and print
part of the CMake command needed to include the dependencies.

### IDEs
Install the dependencies via the method above and include the required CMake
option in the appropriate place in your IDEs settings.

## Contributing 
`Zisa` has been split into smaller libraries to facilitate code reuse. The
motivation to open-source them is that it might reduce your (or my) development
time in some project. The code has a scientific computing background.
Therefore, you're welcome to contribute changes via tickets or pull requests;
and (in true scientific computing fashion) make destructive changes in your own
fork.

`Zisa` is code, please treat it as such and reuse which ever parts you find
useful. If you like you can then share the improvements.
