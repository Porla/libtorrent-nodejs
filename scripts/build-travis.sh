#!/usr/bin/env bash

source ~/.nvm/nvm.sh

set -e -u

if [[ "$TRAVIS_OS_NAME" == "linux" ]]
then
    export CC=gcc-5
    export CXX=g++-5
fi

npm install --build-from-source
npm test

node_modules/.bin/node-pre-gyp package

COMMIT_MESSAGE=$(git show -s --format=%B $TRAVIS_COMMIT | tr -d '\n')
TAG=$TRAVIS_TAG

if [[ "$COMMIT_MESSAGE" =~ ^:shipit:.* ]] && [[ "$TAG" =~ ^v.* ]] ; then
    echo shipping
    node_modules/.bin/node-pre-gyp publish
fi
