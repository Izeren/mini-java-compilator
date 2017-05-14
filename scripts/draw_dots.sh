#!/bin/bash
NPROC=${1:-1}
SOURCE_DIR=${2:-./tests/IRT_builder/dots}
RESULT_DIR=${3:-./tests/IRT_builder/drawn_dots}
FILES=${SOURCE_DIR}/*

draw_dot(){
    echo ${1}
    file_name=$(basename $1)
    dot ${SOURCE_DIR}/${file_name} -Tpng -o ${RESULT_DIR}/${file_name%.*}.png
}
(
for f in ${FILES}
do
    ((i=i%NPROC)); ((i++==0)) && wait
    draw_dot "$f" &
done
)
echo "Dots are drawn, pleasure the watching"
