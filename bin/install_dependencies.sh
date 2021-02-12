#! /usr/bin/env bash
set -e

if [[ "$#" -ne 2 ]]
then
    echo "Usage: $0 COMPILER DESTINATION"
fi

component_name="ZisaCore"
zisa_core_root="$(realpath "$(dirname "$(readlink -f "$0")")"/..)"

install_dir="$("${zisa_core_root}/bin/install_dir.sh" "$1" "$2")"

conan_file="${zisa_core_root}/conanfile.txt"

if [[ -f "$conan_file" ]]
then
   mkdir -p "${install_dir}/conan" && cd "${install_dir}/conan"
   conan install "$conan_file" -s compiler.libcxx=libstdc++11
fi

echo "The dependencies were installed at"
echo "    ${install_dir}"
echo ""
echo "Use"
echo "    cmake -DCMAKE_PROJECT_${component_name}_INCLUDE=${install_dir}/conan/conan_paths.cmake \\ "
echo "          -DCMAKE_MODULE_PATH=${install_dir}/conan \\ "
echo "          -DCMAKE_C_COMPILER=${CC} \\ "
echo "          -DCMAKE_CXX_COMPILER=${CXX} \\ "
echo "          REMAINING_ARGS "
