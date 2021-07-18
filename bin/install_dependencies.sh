#! /usr/bin/env bash
set -e

if [[ "$#" -ne 2 ]]
then
    echo "Usage: $0 COMPILER DESTINATION [--print_install_dir]"
    exit -1
fi

for arg in "$@"
do
    case $arg in
        --print_install_dir)
            PRINT_INSTALL_PATH=1
            ;;
        *)
            ;;
    esac
done

component_name="ZisaCore"
zisa_core_root="$(realpath "$(dirname "$(readlink -f "$0")")"/..)"

install_dir="$("${zisa_core_root}/bin/install_dir.sh" "$1" "$2")"

if [[ ${PRINT_INSTALL_PATH} -eq 1 ]]
then
  echo $install_dir
  exit 0
fi

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
echo "          REMAINING_ARGS "
