#echo "Single" && gcc -pg -o hybridsort hybridsort_single.c
echo "10k" && gcc -pg -o hybridsort hybridsort_10k.c
#echo "50k" && gcc -pg -o hybridsort hybridsort_50k.c

rm out*.txt || true

echo "comp, swap, thresh, size, cpu_time, -->, time" > result.txt

ITER=10	# iterations to run, per step (for averaging)
STEP=1
MAXSIZE=240
THRESH=240
MIN=0

#echo "Threshold = "$MAXSIZE
#bash generator.sh $ITER $MAXSIZE $MAXSIZE # test pure insertion

i=$MAXSIZE
while [[ $i -gt $MIN ]]
do
	SIZE=$i	# sample size to be sorted
	echo "Threshold = "$THRESH", Size = "$SIZE
	
	# .sh -iteration -total_iter -sample_size, -threshold
	bash generator.sh $ITER $SIZE $THRESH
	
	#THRESH=$(( $THRESH - $STEP ))
        i=$(( $i - $STEP ))
done

cp result.txt result.csv
echo "Done!"
