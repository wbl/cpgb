#!/bin/sh

#we have to get nacl's goodies into /build so we can make things with them.
#extra points for doing this on all ABI's and compilers.
host=`hostname`
echo $host
#we need to pick an abi and a compiler that works with it
#right now just pick one. Might break things if we need 64 bit
abi=`./src/nacl-20110221/build/$host/bin/okabi | head -1`
echo $abi

mkdir build
mkdir build/lib
mkdir build/include
incdir="./src/nacl-20110221/build/$host/include/$abi/"
libdir="./src/nacl-20110221/build/$host/lib/$abi/"
cp -R $libdir/ build/lib/
cp -R $incdir/ build/include/