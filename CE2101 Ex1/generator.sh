#!/bin/bash
TIMEFORMAT=%R

ITER=$1
SIZE=$2
THRESH=$3

i=$ITER
while [[ $i -gt 0 ]]
do
	> out"$i".txt
	echo $THRESH >> out"$i".txt 	#thresh
	echo $SIZE >> out"$i".txt	#size
	
	j=$SIZE
	while [[ $j -gt 0 ]]
	do
	    echo $(($SIZE - $j + 1)) >> out"$i".txt #random input values to be sorted
	    #echo $((1 + $RANDOM % $j)) >> out"$i".txt #random input values to be sorted
	    j=$(( $j - 1 ))
	done

	# hybrid
	TIME=$({ time ./hybridsort < out"$i".txt 2>&1 | tail -1 | tr '\n' ', ' >> result.txt ; } 2>&1)
	echo " -->, "$TIME"s" >> result.txt
	gprof hybridsort gmon.out > analysisH.txt
	
	# only merge
	(echo -1 && tail -n +2 out"$i".txt) > out"$i"a.txt && mv out"$i"a.txt out"$i".txt
	TIME=$({ time ./hybridsort < out"$i".txt 2>&1 | tail -1 | tr '\n' ', ' >> result.txt ; } 2>&1)
	echo " -->, "$TIME"s" >> result.txt
	gprof hybridsort gmon.out > analysisM.txt
	
	#echo "Done with iteration "$i

	
	i=$(( $i - 1 ))
done
echo " " >> result.txt
