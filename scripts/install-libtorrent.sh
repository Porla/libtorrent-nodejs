#!/usr/bin/env bash

set -e

libtorrent_commitish=$(<libtorrent-commitish)
echo $libtorrent_commitish

# check to see if libtorrent folder is empty
if [ ! -d "$HOME/libtorrent/lib" ]; then
  git clone https://github.com/arvidn/libtorrent "$HOME/arvidn-libtorrent"
  cd $HOME/arvidn-libtorrent

  git checkout $libtorrent_commitish

  ./autotool.sh

  if [[ "$TRAVIS_OS_NAME" == "osx" ]]
  then
      export CPATH=$CPATH:/usr/local/opt/openssl/include
      export LIBRARY_PATH=$LIBRARY_PATH:/usr/local/opt/openssl/lib

      ./configure --disable-logging --enable-debug=no --enable-deprecated-functions=no --enable-static --prefix=$HOME/libtorrent --with-pic
  else
      export CC=gcc-5
      export CXX=g++-5

      ./configure --disable-logging --enable-debug=no --enable-deprecated-functions=no --enable-static --prefix=$HOME/libtorrent --with-boost=$HOME/boost --with-pic  
  fi

  make && make install
else
  echo "Using cached libtorrent directory."
fi
