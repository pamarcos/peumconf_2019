#! /bin/bash

PLATFORM=$(uname)
if [[ $PLATFORM = Linux ]]; then
    echo "Setting LD_PRELOAD=./libopen.so for Linux"
    export LD_PRELOAD=./libopen.so
elif [[ $PLATFORM = Darwin ]]; then
    echo "Setting DYLD_FORCE_FLAT_NAMESPACE=1 and DYLD_INSERT_LIBRARIES=/libopen.dylib for macOS"
    export DYLD_FORCE_FLAT_NAMESPACE=1
    export DYLD_INSERT_LIBRARIES=./libopen.dylib
else
    echo "Platform not supported"
fi

echo "Calling $1 with proper env variables"
$1 $2 $3 $4 $5 $6 $7 $8