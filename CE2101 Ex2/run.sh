#! /bin/bash

echo "Compiling generator" && gcc -o generator generator.c
echo "Compiling dijkm" && gcc -o dijkm dijk_matrix.c
echo "Compiling dijkl" && gcc -o dijkl dijk_list.c

echo "size, iter, type, CPU Time: CPU Time"> result.csv

ITER=1
MAXSIZE=10
MINSIZE=0

SIZESTEP=10 #$MAXSIZE
MULT=3

i=$MAXSIZE
while [[ $i -gt $MINSIZE ]]
do
    j=$ITER 
    ROOT=$((1 + $RANDOM % $i )) #initial vertex to find path to

    echo "SIZE=$i, ROOT=$ROOT"

    while [[ $j -gt 0 ]]
    do

        > in"$j".txt 

        echo $i >> in"$j".txt
        echo $ROOT >> in"$j".txt

        printf "$i\n$MULT\n$ROOT" | ./generator >> in"$j".txt

        echo -n "$i, $j, Adj Matrix, " >> result.csv
        ./dijkm < in"$j".txt | tail -1 >> result.csv
        #./dijkm < in"$j".txt | tee >(tail -1 >> result.csv) #prints to console too

        sleep 0.003 # 3ms pause to print buffer

        echo -n "$i, $j, Adj List, " >> result.csv
        ./dijkl < in"$j".txt | tail -1 >> result.csv
        #./dijkl < in"$j".txt | tee >(tail -1 >> result.csv) #prints to console too

        sleep 0.003 # 3ms pause to print buffer

        j=$(( $j - 1 ))

    done

    echo "" >> result.csv
    i=$(( $i - $SIZESTEP))
done
