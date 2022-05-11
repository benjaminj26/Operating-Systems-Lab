echo "Enter the first number:";
read num1;

echo "Enter the second number:";
read num2;

echo "1.Add";
echo "2.Subtract";
echo "3.Multiply";
echo "4.Divide";

echo "Enter your choice:";
read choice;

if [ $choice == 1 ]
then
	result=$((num1 + num2));
	echo $result;

elif [ $choice == 2 ]
then
	result=$((num1 - num2));
	echo $result;
	
elif [ $choice == 3 ]
then
	result=$((num1 * num2));
	echo $result;
	
elif [ $choice == 4 ]
then
	result=$((num1 / num2));
	echo $result;

else
	echo "Invalid Input";
fi
