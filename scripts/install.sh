#!/bin/bash
sudo apt-get install -y flex
sudo apt-get install -y bison
sudo apt-get install -y graphviz
rm -rf cmake
mkdir cmake
cd cmake
wget https://cmake.org/files/v3.8/cmake-3.8.0-Linux-x86_64.tar.gz
tar -zxvf cmake-3.8.0-Linux-x86_64.tar.gz
cd ..
sudo chmod +x scripts/configure.sh
sudo chmod +x scripts/build.sh
sudo chmod +x scripts/draw_dots.sh
sudo chmod +x scripts/run_tests.sh
