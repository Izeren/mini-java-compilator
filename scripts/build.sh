#!/bin/bash
rm src/lex.cpp
rm src/lex.h

rm src/bison.hpp
rm src/bison.cpp
rm src/bison.output

cd build
make
