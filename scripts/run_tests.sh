#!/bin/bash
rm -rf tests/IRT_builder/dots
rm -rf tests/IRT_builder/drawn_dots
mkdir tests/IRT_builder/dots
mkdir tests/IRT_builder/drawn_dots
cd src
../build/mini_java_compilator
cd ..
./scripts/draw_dots.sh tests/IRT_builder/dots tests/IRT_builder/drawn_dots
