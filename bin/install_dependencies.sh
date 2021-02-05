#! /usr/bin/env bash

if [[ "$#" -ne 2 ]]
then
    echo "Usage: $0 COMPILER DESTINATION"
fi

component_name="ZisaCore"
zisa_core_root=$(realpath $(dirname $(readlink -f $0))/..)

install_dir=$(${zisa_core_root}/bin/install_dir.sh $1 $2)
source_dir=${install_root}/sources/

conan_file=${zisa_core_root}/conanfile.txt

if [[ -f $conan_file ]]
then
   mkdir -p ${install_dir}/conan && cd ${install_dir}/conan
   conan install $conan_file -s compiler.libcxx=libstdc++11
fi

echo "The dependencies were installed at"
echo "    ${install_dir}"
