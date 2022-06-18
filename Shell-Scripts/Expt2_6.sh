fibonacci=1;
prev1=0;
prev2=1;

echo "Enter the number:";
read number

while [ $fibonacci -le $number ]
do
	echo $fibonacci;
	fibonacci=$((prev1 + prev2));
	prev1=$prev2;
	prev2=$fibonacci;
done
