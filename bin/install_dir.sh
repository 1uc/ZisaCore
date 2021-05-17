#! /usr/bin/env bash

set -e

if [[ "$#" -ne 2 ]]
then
    echo "Usage: $0 COMPILER DESTINATION"
    exit -1
fi

compiler="$1"
compiler_id="$(basename "${compiler}")"
compiler_version="$("$compiler" -dumpversion)"

build_mangled_name="${compiler}__${compiler_version}"
build_sha="$(echo "${build_mangled_name}" | sha1sum | head -c 6)"

install_root=$(realpath -ms "$2")
install_dir="${install_root}/${build_sha}"

echo "${install_dir}"
