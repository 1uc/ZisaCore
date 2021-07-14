# Building
Zisa uses CMake as a to building the project. Well, technically, to configure a
build system which can then build Zisa.

## CMake Primer
The most simple and often practical way of using CMake is on the command line to
generate Make files. This can be done by

    $ cmake ${MANY_FLAGS} -DCMAKE_BUILD_TYPE=${BUILD_TYPE} -B ${BUILD_DIR}

which will set up everything in the folder `${BUILD_DIR}` mostly called
`build` and virtually never `.`. Nothing stops you from having several build
folders each using either different dependencies or compilers.

In order to actually compile one can type

    $ cmake --build ${BUILD_DIR} --parallel $(nproc)

which is essentially

    $ cd ${BUILD_DIR}; make -j $(nproc); cd -

Finally, it pays to check if the compilation commands correspond to something
meaningful. Which is achieved by `make VERBOSE=1`.

Equipped with this knowledge using CMake revolves around finding the correct
value for `${MANY_FLAGS}`, see [Project specific flags](@ref cmake_flags) for help
with this problem.

### Globbing source files
The convincing argument for not globbing source files is that if one switches
Git branches files might appear or vanish; and if `CMakeLists.txt` does not
change (very likely), then `cmake` won't be run again, resulting in a
misconfigured build.

Obviously, adding the files manually is unacceptable. However, nothing is
stopping us from have a script add them manually for us. This script is called
`bin/update_cmake.py`. For every subfolder it simply lists the source files
contained in that folder in a new `CMakeLists.txt` located in that subfolder. A
simple `add_subdirectory` pulls in the files.

### Deleting build folders
Personally, when facing strange issues with CMake, I think it helps to point
CMake to a fresh location, either by changing the `${BUILD_DIR}` or by deleting
it.

## Project specific flags                                         {#cmake_flags}
The script for installing the dependencies generates part of the CMake command
required for compiling Zisa. You'll need to add flags to control which
dependencies should be used:

  * `-DZISA_HAS_CUDA={0,1}` for CUDA.
  * `-DZISA_HAS_HDF5={0,1}` for HDF5 I/O.
  * `-DZISA_HAS_NETCDF={0,1}` for NetCDF I/O.

Further, you should choose a build type:

  * `Debug` CMake built in.
  * `FastDebug` optimized build with debug symbols and assertions.
  * `Release` CMake built in.

Running an unoptimized build can be very slow. Therefore, if you need only
semi-meaningful backtraces and want assertions, `FastDebug` is a good
choice. Now, for more specialized settings we provide:

  * `GPERFTOOLS` adds the flags required for `gperftools`, a sampling profiler.
  * `ASAN` adds the flags for Clangs AdressSanitizer.
  * `UBSAN` adds the flags for Clangs undefined behaviour sanitizer.

all three are based on an optimized build with debug symbols. Note that `ASAN`
and `UBSAN` expect the Clang compilers. The details can be found in `cmake/`.


## IDEs
The tested way of using Zisa in an IDE is to configure the IDE to pass the
required flags to CMake. In order to figure out which flags are needed you
could follow the instructions for the CLI and once you have the correct flags
copy-paste them into the settings menu of the IDE.
