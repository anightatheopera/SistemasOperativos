#!/bin/sh

for((i = 0 ; i <1000; i++))
do 
    echo `./main -i "yuh$i" $i`
done