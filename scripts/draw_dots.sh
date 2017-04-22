#!/bin/bash
SOURCE_DIR=${1:-./tests/IRT_builder/dots}
RESULT_DIR=${2:-./tests/IRT_builder/drawn_dots}
FILES=${SOURCE_DIR}/*
for f in ${FILES}
do
    echo ${f}
    file_name=$(basename $f)
    dot ${SOURCE_DIR}/${file_name} -Tpng -o ${RESULT_DIR}/${file_name%.*}.png
done