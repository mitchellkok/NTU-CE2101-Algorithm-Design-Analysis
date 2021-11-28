gcc -o hybridsort hybridsort_10k.c

> testM_out.txt
> testI_out.txt
> testH_out.txt

start=0
end=40000

echo -1 > testM.txt
echo $(( end + 1 )) > testI.txt
echo 8 > testH.txt

echo $end | tee -a testM.txt testH.txt testI.txt 1>/dev/null

while [[ $start -lt $end ]]
do
	
	echo $((1 + $RANDOM % $end)) | tee -a testM.txt testH.txt testI.txt 1>/dev/null
	
	start=$(( $start + 1 ))
done

echo " " | tee -a testM.txt testH.txt testI.txt 1>/dev/null

#./hybridsort < testM.txt >> testM_out.txt
#echo "Merge done"

#./hybridsort < testI.txt >> testI_out.txt
#echo "Insertion done"

./hybridsort < testH.txt >> testH_out.txt
echo "Hybrid done"
