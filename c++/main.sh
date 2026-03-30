#!/bin/bash

build_dir=$(pwd)/build
bin_dir=$(pwd)/bin

if [ ! -d $build_dir ]; then
    mkdir $build_dir
fi

if [ ! -d $bin_dir ]; then
    mkdir $bin_dir
fi

cd $build_dir
rm -rf *
cmake ..
make
echo `date`": build finish" >> ../main.log

echo `date`": $bin_dir/usr run start " >> ../main.log
gnome-terminal --working-directory=$bin_dir --command=./usr

echo `date`": $bin_dir/customer run start " >> ../main.log
gnome-terminal --working-directory=$bin_dir --command=./customer


