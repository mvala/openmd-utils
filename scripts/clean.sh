#!/bin/bash

OMD_UTILS_DIR="$(dirname $(dirname $(readlink -m $0)))"

for d in bin lib lib64 share pars build; do
  [ -d $OMD_UTILS_DIR/$d ] && rm -rf $OMD_UTILS_DIR/$d
done
rm -f $OMD_UTILS_DIR/*.spec
