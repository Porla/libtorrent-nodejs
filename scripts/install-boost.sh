#!/bin/sh
set -e
# check to see if boost folder is empty
if [ ! -d "$HOME/boost/lib" ]; then
  wget http://downloads.sourceforge.net/project/boost/boost/1.65.1/boost_1_65_1.tar.gz
  tar -xzvf boost_1_65_1.tar.gz > /dev/null
  cd boost_1_65_1 && ./bootstrap.sh --prefix=$HOME/boost --with-libraries=system && ./b2 cxxflags=-fPIC install >> /dev/null
else
  echo "Using cached boost directory."
fi
