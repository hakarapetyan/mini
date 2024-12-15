#!/bin/bash

path="`pwd`/$1"
mkdir -p $path
if [ -d "readline-8.2" ]; then
    echo "Directory exists."
else
	curl -O https://ftp.gnu.org/gnu/readline/readline-8.2.tar.gz
	tar -xpf readline-8.2.tar.gz
	rm -rf readline-8.2.tar.gz
fi
cd readline-8.2 && ./configure --prefix=$path
make
make install
