
In C/C++ the number of digits a long long int can have is a maximum of 20. And the question is to store the 22 digit number which is not easy to store in any kind of primitive type. So to deal with this type of problem let’s design a new data type which is going to be called BigInt.


1.Add two big integers.
2.Subtract two big integers
3.Multiply two big integers.
4.ivide two big integers.
5.Modulo two big integers
6.Raise a big integer to a power
7.The square root of a big integer
8.Comparison between two big integers to check which is greater and which is smaller.
9.Find the number of digits in the big integer.
10.Print the big integer.
11.Convert an integer to a big integer.
12.Applications Of BigInt:
13.Below are some basic applications of the new data type, BigInt:


1.Calculating the Fibonacci number of a large number.
2.Calculating the Catalan number of a large number
3.Calculating the Factorial of a big integer.

# Approach:
To create a new data type of big integers following concepts are being implemented:

C++ strings in that we can store our numbers in the form of characters (in reverse order for efficiency purposes) such that using strings we can store very big numbers also.
For the addition/subtraction operation of two big integers, use the basic math for addition which says that add the corresponding two digits and if some carry is generated add it to the sum of the next digits and repeat this process until all digits are added/subtracted.
Similarly, for the multiplication of two numbers, use the basic mathematics approach which states that multiply every digit of one number with the other complete number and at last add all the numbers we get in multiplication.
The following operations are being performed on BigInt-


1.Defining some big integers.
2.Checking the number of digits in the big integer.
3.Post/Pre Incrementation or Decrementation
4.Adding two big integers.
5.Subtracting two big integers.
6.Multiplying two big integers.
7.Divide two big integers
8.Modulo of two big integers
9.The square root of a big integer (floor integer value)
10.Raise a big integer to a power
11.Converting a simple integer to a big integer.
12.Calculating Fibonacci up to 10 000. (even 100000 but slower)
13.Calculating Factorial up to 1 000.
14.Calculating Catalan up to 1 000.
15.Checking which big integer is greater and which is smaller.
