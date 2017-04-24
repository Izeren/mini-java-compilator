#!/bin/bash
rm -rf build
mkdir build
cd build
${1:-../cmake/cmake-3.8.0-Linux-x86_64/bin/cmake} ..
