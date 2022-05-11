echo "Enter a number:";
read number;

fact=1;
counter=1;

while [ $counter -le $number ]
do
	fact=$((fact * counter));
	counter=$((counter + 1));
done

echo $fact
