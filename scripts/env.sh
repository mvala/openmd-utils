#!/bin/bash

OMD_UTILS_DIR="$(dirname $(dirname $(readlink -m ${BASH_ARGV[0]})))"

export PATH="$OMD_UTILS_DIR/bin:$OMD_UTILS_DIR/scripts:$PATH"
export LD_LIBRARY_PATH="$OMD_UTILS_DIR/lib:$OMD_UTILS_DIR/lib64:$LD_LIBRARY_PATH"
export OPENMD_UTILS_MACRO_DIR="$OMD_UTILS_DIR/macros"
