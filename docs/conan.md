# Conan
Conan is a wonderful tool to download and install compiled libraries to a local
folder on your computer. In addition it generates the necesary information to
link against these local versions.

It can be installed either using the package manager or

    pip install --user conan

(or `pip3` depending on your Linux distribution).

## Quick Conan Primer
### Conan Profiles
In order to obtain ABI compatible libraries, Conan must be told which compiler,
compiler version and which standard library should be used. My initial faulty
assumption was it would just deduce everything from the environment variable
`CC`. Instead Conan has a concept of "profiles" which are textfiles containing
all the relevant information.

The TL;DR version is
    conan profile show default

to see what can/needs to be modified. Then create a new profile in the folder
`~/.conan/profiles`. Use this profile by

    conan install CONANFILE --profile PROFILE

where `CONANFILE` is typically `../conanfile.txt` and `PROFILE` is the name of
the file you created in `~/.conan/profiles`, e.g., `default` if you want to
redundanty specify the default profile.

### C++11 Standard Library
Modern C++ links to a C++11 compatible version of the standard library. Conan
must be told to use the modern library, either by modifying a profile (possibly
the default) or by adding

    conan CONANFILE -s compiler.libcxx=libstdc++11


## Combining CMake and Conan
Conan and CMake work very nicely together. There are several ways of combining
the two. The rationale is to avoid a strong coupling of the two. Therefore, we
strive for a `CMakeLists.txt` which does not contain Conan specific
instruction. After all Conan is just a way of obtaining libraries and not the
way. In particular, if all dependencies are installed in standard locations
(meaning CMake can find them), then Conan should not be needed.

The two *generators* we use are

  * **cmake_find_package** which automatically generates `FindXYZ.cmake`.
  * **cmake_paths** which generates a file with the CMake variable required to
  find the generated `FindXYZ.cmake` modules.

Therefore, if we were to `include(conan_paths.cmake)`, CMake would pickup the
Conan generated find modules. Fortunately, there's an interesting trick to
avoid literally including the file in `CMakeLists.txt`. Namely, CMake has a
command line argument `-DCMAKE_PROJECT_${PROJECT}_INCLUDE` which can be used to
include a file, e.g., `conan_paths.cmake`.


[Conan]: https://conan.io
