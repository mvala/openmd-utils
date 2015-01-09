#!/bin/bash

if [ -z "$1" ];then
    echo "./%0 <name>"
    exit 1
fi
:
cp -f TOmdSelectorExample.h TOmd${1}Selector.h
cp -f TOmdSelectorExample.cxx TOmd${1}Selector.cxx

sed -i -e 's/TOmdSelectorExample/TOmd'$1'Selector/g' TOmd${1}Selector.h
sed -i -e 's/TOmdSelectorExample/TOmd'$1'Selector/g' TOmd${1}Selector.cxx

echo "Files 'TOmd${1}Selector.h' and 'TOmd${1}Selector.cxx' were created."
