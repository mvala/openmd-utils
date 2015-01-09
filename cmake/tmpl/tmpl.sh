#!/bin/bash

if [ -z "$1" ];then
    echo "./%0 <name>"
    exit 1
fi

cp -f TOmdExample.h TOmd${1}.h
cp -f TOmdExample.cxx TOmd${1}.cxx

sed -i -e 's/TOmdExample/TOmd'$1'/g' TOmd${1}.h
sed -i -e 's/TOmdExample/TOmd'$1'/g' TOmd${1}.cxx

echo "Files 'TOmd${1}.h' and 'TOmd${1}.cxx' were created."
