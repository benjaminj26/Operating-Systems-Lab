a=1;

while [ $a -le 10 ]
do
	echo $a;
	a=`expr $a + 1`;
done
