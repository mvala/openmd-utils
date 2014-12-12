#!/bin/bash

if [ -z "$1" ];then
    echo "./%0 <name>"
    exit 1
fi

cp -f TOmdExample.h TFx${1}.h
cp -f TOmdExample.cxx TFx${1}.cxx

sed -i -e 's/TOmdExample/TFx'$1'/g' TFx${1}.h
sed -i -e 's/TOmdExample/TFx'$1'/g' TFx${1}.cxx

echo "Files 'TOmd${1}.h' and 'TOmd${1}.cxx' were created."
