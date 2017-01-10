#!/bin/bash

OMD_UTILS_DIR="$(dirname $(dirname $(readlink -m $0)))"

[ "$1" = "clean" ] && { shift; rm -rf $OMD_UTILS_DIR/build; }
[ -d $OMD_UTILS_DIR/build ] ||  mkdir $OMD_UTILS_DIR/build

cd $OMD_UTILS_DIR/build || exit 1
[ -f Makefile ] || cmake -DCMAKE_INSTALL_PREFIX=$OMD_UTILS_DIR -DCMAKE_BUILD_TYPE=RelWithDebInfo ../
make -j$(nproc) $*

