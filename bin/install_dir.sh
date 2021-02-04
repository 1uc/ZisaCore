#! /usr/bin/env bash

if [[ "$#" -ne 2 ]]
then
    echo "Usage: $0 COMPILER DESTINATION"
fi

component_name="ZisaCore"

compiler=$1
compiler_id=$(basename ${compiler})
compiler_version=$($compiler -dumpversion)

install_root=$2
install_dir=${install_root}/${component_name}/${compiler_id}/${compiler_version}

echo ${install_dir}
