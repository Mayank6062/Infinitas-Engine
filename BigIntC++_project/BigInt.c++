// C++ program to implement
// the above approach
#include <bits/stdc++.h>

using namespace std;

class BigInt{
	string digits;
public:

	//Constructors:
	BigInt(unsigned long long n = 0);
	BigInt(string &);// String ko BigInt mein convert karega
	BigInt(const char *);//const char * ka matlab yeh string read-only hai, aur modify nahi ki ja sakti.
	BigInt(BigInt &);//Ye copy constructor hai. Iska kaam ek BigInt object ko doosre BigInt object se copy karna hai.

	//Helper Functions:
    //Ye friend function hai, jo BigInt class ka private data directly access kar sakta hai.
    //BigInt &a reference ko pass kiya jata hai, to ye original object ko directly modify karega, copy nahi banayega.
	friend void divide_by_2(BigInt &a);
	friend bool Null(const BigInt &);//object ka value zero (null) hai ya nahi.//const BigInt & pass karta hai, jisse BigInt object ko modify nahi kiya ja sakta, sirf read kiya ja sakta hai.
	friend int Length(const BigInt &);//digits ka count 
	int operator[](const int)const;//Ye operator overloading function hai jo BigInt class ke objects ke liye array-style indexing allow karta hai.//not modified obj //nigint obj ke digit ko individual access by []operator

			/* * * * Operator Overloading * * * */

	//Direct assignment overload(=)
    //BigInt & ka matlab hai ki ye function reference return karega, jisse chain assignment possible hota hai (e.g. a = b = c).
//const BigInt & ka matlab hai ki tum jo object pass kar rahe ho (right-hand side object), usko modify nahi kiya jayega.
	BigInt &operator=(const BigInt &);

	//Post/Pre - Incrementation oprator overlod without fried function
	BigInt &operator++();// pre-increment operator (++) ko overload //Return type BigInt & hota hai, jisse original object ko modify kiya jata hai.
	BigInt operator++(int temp);// post-increment operator (++) ko overload //int temp ek dummy parameter hai jo compiler ko differentiate karne mein madad karta hai pre-increment aur post-increment ke beech.
	BigInt &operator--();
	BigInt operator--(int temp);

	//Addition and Subtraction //operator overlod by using friend fun.
    //const ===> original obj not modifed
    //Yeh sab operators BigInt objects ko integers ki tarah treat karte hain, jisse tum easily addition aur subtraction operations perform kar sakte ho.
	friend BigInt &operator+=(BigInt &, const BigInt &);//+= operator ko overload //BigInt & return type ka matlab hai ki ye original object ko modify karega aur reference return karega, jisse tum chain addition kar sakte ho (e.g., a += b += c).//const BigInt & means obj only read not modified
	friend BigInt operator+(const BigInt &, const BigInt &);//obj3 = obj1 + obj2 , obj3 return bina original obj3 ko modify kiye.//const BigInt & dono parameters ke liye diya gaya hai, iska matlab hai ki tum original BigInt objects ko modify nahi karoge, bas unka sum return karoge.ob1 and obj2 not modified original
	friend BigInt operator-(const BigInt &, const BigInt &);////obj3 = obj1 - obj2 , obj3 return bina original obj3 ko modify kiye.//const BigInt & dono parameters ke liye diya gaya hai, iska matlab hai ki tum original BigInt objects ko modify nahi karoge, bas unka sub return karoge.ob1 and obj2 not modified original
	friend BigInt &operator-=(BigInt &, const BigInt &);//BigInt & return type ka matlab hai ki original object ko modify kiya jata hai aur reference return kiya jata hai, jisse chain subtraction possible hota hai (e.g., a -= b -= c).

	//Comparison operators //BigInt objects ke beech comparison karne ke liye.
	friend bool operator==(const BigInt &, const BigInt &);//BigInt objects ko compare karta hai ki kya dono equal hain.
	friend bool operator!=(const BigInt &, const BigInt &);//Check karta hai ki kya dono objects unequal hain
	friend bool operator>(const BigInt &, const BigInt &);//Pehla BigInt doosre se bada hai ya nahi, check karta hai
	friend bool operator>=(const BigInt &, const BigInt &);//Pehla BigInt doosre ke barabar ya usse bada hai ya nahi, check karta hai.
	friend bool operator<(const BigInt &, const BigInt &);
	friend bool operator<=(const BigInt &, const BigInt &);

	//Multiplication and Division
	friend BigInt &operator*=(BigInt &, const BigInt &);//jisme result pehle wale BigInt object mein assign ho jata hai.
	friend BigInt operator*(const BigInt &, const BigInt &);//Do BigInt objects ko multiply karta hai aur naya BigInt object return karta hai.
	friend BigInt &operator/=(BigInt &, const BigInt &);//jisme pehle wale object ko divide karke result assign kiya jata hai.
	friend BigInt operator/(const BigInt &, const BigInt &);//Do BigInt objects ko divide karta hai aur naya BigInt object return karta hai.

	//Modulo
	friend BigInt operator%(const BigInt &, const BigInt &); //Do BigInt objects ke beech modulo operation perform karta hai aur naya BigInt object return karta hai.
	friend BigInt &operator%=(BigInt &, const BigInt &);//isme result ko pehle wale object mein assign kar diya jata hai.

	//Power Function
	friend BigInt &operator^=(BigInt &,const BigInt &);// jisme result pehle wale BigInt object mein store hota hai.
	friend BigInt operator^(BigInt &, const BigInt &);//Exponentiation operator ko overload karta hai jisse do BigInt objects ke beech exponentiation perform kiya jata hai.
	
	//Square Root Function
	friend BigInt sqrt(BigInt &a);//BigInt object ka square root return karta hai.

	//Read and Write
    //cin >> a;  // Input lo
   //cout << a; // Output dikhana

	friend ostream &operator<<(ostream &,const BigInt &);//BigInt object ko output stream (e.g., cout) me print karta hai.
	friend istream &operator>>(istream &, BigInt &);// Input stream se BigInt object me input leta hai (e.g., cin se).

	//Others
	friend BigInt NthCatalan(int n);//nth Catalan number return karta hai.
	friend BigInt NthFibonacci(int n);
	friend BigInt Factorial(int n);
};

//class :: constructor
BigInt::BigInt(string & s){// BigInt class ka constructor hai jo ek string object ko input le kar usse BigInt object me convert karta hai.
	digits = "";
	int n = s.size();
	for (int i = n - 1; i >= 0;i--){
		if(!isdigit(s[i]))
			throw("ERROR");
		digits.push_back(s[i] - '0');//number ko reverse order me store karega.
	}
}


BigInt::BigInt(unsigned long long nr){//unsigned long long integer ko input le kar usse BigInt object me convert karta hai.
	do{
		digits.push_back(nr % 10);
		nr /= 10;
	} while (nr);
}


BigInt::BigInt(const char *s){ //BigInt class ka constructor hai jo ek C-style character array (string) ko input le kar usse BigInt object me convert karta hai
	digits = ""; //const char *s ek character array hai jo ek number ko string ke form me represent karta hai.
	for (int i = strlen(s) - 1; i >= 0;i--)
	{
		if(!isdigit(s[i]))
			throw("ERROR");
		digits.push_back(s[i] - '0');
	}
}


BigInt::BigInt(BigInt & a){//BigInt object ko copy karta hai aur ek naya BigInt object banata h//BigInt &a ek reference hai us BigInt object ka jise copy karna hai.
	digits = a.digits;//object ke digits ko doosre object ke digits se copy kiya ja raha h//BigInt object ko doosre BigInt object ke reference se initialize karna hai.
}


bool Null(const BigInt& a){ //bigInt object zero hai ya nahi.//const BigInt& a ek constant reference hai BigInt object ka, jise check karna hai. Constant reference ka istemal isliye kiya gaya hai taaki function ke andar a object ko modify na kiya ja sake.
	if(a.digits.size() == 1 && a.digits[0] == 0)
		return true;
	return false;
}


int Length(const BigInt & a){
	return a.digits.size();
}

//class::constructor //const int index ek integer hai jo indicate karta hai ki aap kis index par stored digit ko access karna chahte hain.
int BigInt::operator[](const int index)const{//eh operator[] function BigInt class ka ek member function hai. Iska return type int hai, jo specific index par digit ko return karega.
	if(digits.size() <= index || index < 0)
		throw("ERROR");
	return digits[index];
}

//operator== -> function name 
bool operator==(const BigInt &a, const BigInt &b){//const=> function ke and bigint obj a, b ko modified nhi kar sakte 
	return a.digits == b.digits;//object compare
}


bool operator!=(const BigInt & a,const BigInt &b){
	return !(a == b);
}


bool operator<(const BigInt&a,const BigInt&b){
	int n = Length(a), m = Length(b);
	if(n != m)//length compare
		return n < m;//length compare direct jiski length kam bo chhota hoga
	while(n--) //yadi length barabar h dono ki to digit comare karege 
		if(a.digits[n] != b.digits[n])//a aur b ke digits ko last se first tak compare kiya ja raha hai.bz reverse orer me store kiye gaye h 
			return a.digits[n] < b.digits[n];
	return false; //5555 == 5555 jab koi bhi digit alag na to false
}


bool operator>(const BigInt&a,const BigInt&b){
	return a > b;
}


bool operator>=(const BigInt&a,const BigInt&b){
	return !(a < b);
}


bool operator<=(const BigInt&a,const BigInt&b){
	return !(a > b);
}

//iska return type BigInt & hai, jo is object ka reference return karega jisme assignment kiya gaya hai. Yeh chaining of assignment ko allow karta hai.
//class returntype:: function_name
BigInt &BigInt::operator=(const BigInt &a){//operator= function overload kiya gaya hai jo BigInt class ke objects ke liye direct assignment operator ko define karta hai
	digits = a.digits;//Yeh line a ke digits member ko current object ke digits member mein assign karta hai.
	return *this;//Yeh line current object ka reference return karta hai. *this current object ko refer karta hai.
}

//return type BigInt & hai, jo is object ka reference return karega jisme increment kiya gaya hai.
BigInt &BigInt::operator++(){//overload preincrement ++
	int i, n = digits.size();
	for (i = 0; i < n && digits[i] == 9;i++)
		digits[i] = 0;
	if(i == n) //Agar loop ke baad i ki value n ke barabar hai, iska matlab hai ki sabhi digits 9 the (for example, 999). jo result ko 1000 bana deta hai.
		digits.push_back(1);
	else
		digits[i]++; //bz digits me data reverse order me store h
	return *this;//Yeh line current object ka reference return karta hai. *this current object ko refer karta hai.
}


BigInt BigInt::operator++(int temp){//overload postincrement ++//int temp parameter sirf yeh indicate karne ke liye hai ki yeh post-increment operator hai. Iska actual mein koi use nahi hai.
	BigInt aux; //bigint type ka ek temparary obj.
	aux = *this;//assing currnt obj. to bigint obj.
	++(*this); //call preincremt operatior jo upper define h 
	return aux; //return bigint current obj increment ke pehle ki value
}


//Yeh function BigInt reference return karta hai (& se indicate hota hai ki yeh current object ko return karega
BigInt &BigInt::operator--(){////overload peeincrement --
	if(digits[0] == 0 && digits.size() == 1)
		throw("UNDERFLOW");
	int i, n = digits.size();
	for (i = 0; digits[i] == 0 && i < n;i++) //100 = > 001(store) -- => 990 last 0 pop() => 99
		digits[i] = 9; //eh loop har leading zero ko 9 se replace karta hai, jab tak koi non-zero digit nahi mil jata.
	digits[i]--; //Agar leading zeros the, toh unhe 9 se replace karne ke baad first non-zero digit ko 1 se ghata diya jayega.
	if(n > 1 && digits[n - 1] == 0)
		digits.pop_back();//Agar last digit 0 hai, toh pop_back() function ka use karke last element ko remove kar deta hai, taaki BigInt object ka size sahi rahe.
	return *this;
}


BigInt BigInt::operator--(int temp){///overload postincrement --///int temp ek dummy parameter 
	BigInt aux;
	aux = *this;
	--(*this); //call preincremtn -- above
	return aux;//return decement hone se pehle ki value
    //BigInt a("100");
    //BigInt b = a--; // b ab 100 hoga, lekin a ab 99 hoga.
}


BigInt &operator+=(BigInt &a,const BigInt& b){//overload += //obja = obja + objb
	int t = 0; //for carry store  
    int s; //use for current digit ka sum
    int i; //for loop
	int n = Length(a), m = Length(b);//len fun call
	if(m > n)
		a.digits.append(m - n, 0);//a.digits mein m - n number of zeroes append kiye jate hain.
	n = Length(a);//updated laength
	for (i = 0; i < n;i++){
		if(i < m) //i < b.len
			s = (a.digits[i] + b.digits[i]) + t;
		else
			s = a.digits[i] + t;
		t = s / 10;
		a.digits[i] = (s % 10);
	}
	if(t)//Agar t (carry) non-zero hai, toh isse a.digits mein append kiya jata hai.
		a.digits.push_back(t);
	return a;//a ka reference return karta hai,
}


BigInt operator+(const BigInt &a, const BigInt &b){//overloa + 
	BigInt temp;
	temp = a;
	temp += b; //call above fuction t(a) = t(a) + b
	return temp;
}


BigInt &operator-=(BigInt&a,const BigInt &b){//overload -= => a = a-b //a can modified in the fun but b can not 
	if(a < b)
		throw("UNDERFLOW");
	int n = Length(a), m = Length(b);
	int i; 
    int t = 0;//carry store //jo borrow ko track karta hai
    int s;//current sub result store
	for (i = 0; i < n; i++){ //Yeh loop a ki digits par iterate karta hai.
		if(i < m)// i < b.len
			s = a.digits[i] - b.digits[i] + t;
		else
			s = a.digits[i]+ t;
		if(s < 0)
			s += 10,//Agar subtraction ke baad s negative hai, toh s mein 10 add kiya jata hai aur t ko
			t = -1; //-1 set kiya jata hai, jo borrow ko indicate karta hai.
		else
			t = 0;
		a.digits[i] = s;
	}
	while(n > 1 && a.digits[n - 1] == 0) //Yeh loop unnecessary leading zeros ko remove karta hai, agar last digit zero hai toh woh remove hota rahega jab tak n 1 se bada hai.
		a.digits.pop_back(),
		n--;
	return a;
}



BigInt operator-(const BigInt& a,const BigInt&b){
	BigInt temp;
	temp = a;
	temp -= b;//call above
	return temp;
}



BigInt &operator*=(BigInt &a, const BigInt &b){
	if(Null(a) || Null(b)){//Agar a ya b zero hai (i.e. null), toh result zero hona chahiye. Isliye agar Null function true return karta hai, toh a ko zero se replace kar diya jata hai aur return kiya jata hai.
		a = BigInt(); //a = a * 0
		return a;
	}
	int n = a.digits.size(), m = b.digits.size();
	vector<int> v(n + m, 0); //v ek vector hai, jisme result ke digits store kiye jayenge. Iska size n + m set kiya gaya hai, kyunki maximum result ka size in dono ke size ka sum ho sakta hai.
	for (int i = 0; i < n;i++)
		for (int j = 0; j < m;j++){
			v[i + j] += (a.digits[i] ) * (b.digits[j]); //Yeh nested loop a ke har digit ko b ke har digit se multiply karta hai.
                                                        //Multiplication ka result v[i + j] mein add kiya jata hai. Yeh correct position par result store karta hai, jisse carry handle kiya ja sake.
		}
	n += m;
	a.digits.resize(v.size()); //a Digits: a ke digits vector ka size adjust kiya jata hai taaki result ko store kiya ja sake.
	for (int s, i = 0, t = 0; i < n; i++) //Yeh loop result ke vector v mein carry ko handle karta hai.
	{
		s = t + v[i];
		v[i] = s % 10;
		t = s / 10;
		a.digits[i] = v[i] ;
	}
    /*Har position ke liye, carry t ko current digit s ke saath add kiya jata hai.
v[i] mein s % 10 ko store kiya jata hai (jo current digit hota hai), aur carry t = s / 10 ko next digit ke liye carry forward kiya jata hai.*/
	for (int i = n - 1; i >= 1 && !v[i];i--) //Remove Leading Zeros: Yeh loop result se unnecessary leading zeros ko remove karta hai, taaki result correct form mein aaye.
			a.digits.pop_back();
	return a;
}



BigInt operator*(const BigInt&a,const BigInt&b){
	BigInt temp;
	temp = a;
	temp *= b; //call above
	return temp;
}


BigInt &operator/=(BigInt& a,const BigInt &b){
	if(Null(b))
		throw("Arithmetic Error: Division By 0");
	if(a < b){
		a = BigInt();//a is set to 0 by creating a new BigInt object initialized to zero.
		return a;// ret 0 
	}
	if(a == b){
		a = BigInt(1);
		return a;// ret 1
	}
	int i, lgcat = 0, cc;
	int n = Length(a), m = Length(b);
	vector<int> cat(n, 0);//used to store quotiuent digits
	BigInt t;//t is a temporary BigInt obj used to store the current part of a being divided by b
    //Start from the most significant digit of a (i.e., the last digit in the digits vector). Keep adding digits from a to t while t * 10 + a.digits[i] is still smaller than b. This builds the portion of a that will be divided by b
	for (i = n - 1; t * 10 + a.digits[i] < b;i--){
		t *= 10;
		t += a.digits[i] ;
	}
	for (; i >= 0; i--){
		t = t * 10 + a.digits[i];
		for (cc = 9; cc * b > t;cc--);
		t -= cc * b;
		cat[lgcat++] = cc;
	}
	a.digits.resize(cat.size());//Once the division is done, store the calculated quotient digits back into a.digits from cat.
// the size of a.digits is adjusted to the length of the quotient.
	for (i = 0; i < lgcat; i++)
		a.digits[i] = cat[lgcat - i - 1];
	a.digits.resize(lgcat);
	return a;
}



BigInt operator/(const BigInt &a,const BigInt &b){
	BigInt temp;
	temp = a;
	temp /= b; //call
	return temp;
}



BigInt &operator%=(BigInt& a,const BigInt &b){
	if(Null(b))
		throw("Arithmetic Error: Division By 0");
	if(a < b){
		return a;
	}
	if(a == b){
		a = BigInt();
		return a;
	}
	int i, lgcat = 0, cc;
	int n = Length(a), m = Length(b);
	vector<int> cat(n, 0);
	BigInt t;//temp obj
    //It then iterates over the digits of a from the most significant to the least significant.
	for (i = n - 1; t * 10 + a.digits[i] < b; i--){//For each digit, it multiplies t by 10 and adds the current digit of a: t = t * 10 + a.digits[i];.
		t *= 10;
		t += a.digits[i];
	}
    /*It then determines the largest integer cc such that cc * b <= t. This is done by decrementing cc from 9 until cc * b is less than or equal to t.
After finding cc, it subtracts cc * b from t: t -= cc * b;.*/
	for (; i >= 0; i--){
		t = t * 10 + a.digits[i];
		for (cc = 9; cc * b > t;cc--);
		t -= cc * b;
		cat[lgcat++] = cc;
	}
	a = t;
	return a;
}



BigInt operator%(const BigInt &a,const BigInt &b){
	BigInt temp;
	temp = a;
	temp %= b;//call
	return temp;
}


// ^= here this is the power operator not the zor operator
BigInt &operator^=(BigInt & a,const BigInt & b){// (a ^= b). base ^ exponent
	BigInt Exponent, Base(a);//The Base is initialized as a copy of a because we will modify it.
	Exponent = b;
	a = 1;//a is initialized to 1, as any number raised to the power of 0 is 1.
	while(!Null(Exponent)){//until power is not equal to 0
		if(Exponent[0] & 1)/*Odd exponent check: Exponent[0] & 1 checks if the least significant bit of Exponent is 1, which means Exponent is odd. If it's odd, a is multiplied by Base.This step handles the case where the exponent is odd, reducing the problem size by one (i.e., a *= Base when Exponent is odd).*/
			a *= Base;
		Base *= Base;//else When the exponent is even, we square the base 
		divide_by_2(Exponent);//Exponent /= 2, In binary, dividing by 2 is equivalent to a right shift, which is very efficient.
	}
	return a;
}


BigInt operator^(BigInt & a,BigInt & b){
	BigInt temp(a);
	temp ^= b;//call
	return temp;
}


void divide_by_2(BigInt & a){
	int add = 0;//add is used to carry over any remainder from previous digits when performing the division.
	for (int i = a.digits.size() - 1; i >= 0;i--){
		int digit = (a.digits[i] >> 1) + add; //The right-shift operator (>> 1) divides the current digit by 2.//add is added to account for any carry from the previous digit
        /*This extracts the least significant bit of the current digit (a.digits[i] & 1).
If the digit is odd (& 1 is 1), the carry-over add is set to 5, because dividing an odd number by 2 results in a decimal point of .5, and multiplying 0.5 by 10 (to shift for the next digit) gives 5.*/
		add = ((a.digits[i] & 1) * 5);
		a.digits[i] = digit;//The current digit is updated to the value of digit after dividing by 2 and adjusting for any carry-over.
	}
	while(a.digits.size() > 1 && !a.digits.back())//This loop removes any leading zeros from the BigInt (except for the case where the number is just zero itself).
		a.digits.pop_back();//a.digits.back() gives the most significant digit, and the loop pops the digit if it is zero.
}


BigInt sqrt(BigInt & a){
	BigInt left(1), right(a), v(1), mid, prod;
	divide_by_2(right);
	while(left <= right){
		mid += left;
		mid += right;
		divide_by_2(mid);//mid = l + r /2
		prod = (mid * mid);
		if(prod <= a){
			v = mid;
			++mid;
			left = mid;
		}
		else{
			--mid;
			right = mid;
		}
		mid = BigInt();
	}
	return v;
}


BigInt NthCatalan(int n){
	BigInt a(1),b;
	for (int i = 2; i <= n;i++)
		a *= i;
	b = a;
	for (int i = n + 1; i <= 2 * n;i++)
		b *= i;
	a *= a;
	a *= (n + 1);
	b /= a;
	return b;
}



BigInt NthFibonacci(int n){
	BigInt a(1), b(1), c;
	if(!n)
		return c;
	n--;
	while(n--){
		c = a + b;
		b = a;
		a = c;
	}
	return b;
}



BigInt Factorial(int n){
	BigInt f(1);
	for (int i = 2; i <= n;i++)
		f *= i;
	return f;
}


/*This operator>> function overload reads a BigInt from an input stream (istream) and stores the number in reverse order in the digits vector of the BigInt object*/
istream &operator>>(istream &in, BigInt &a) {
    string s;
    in >> s;
    int n = s.size();
    a.digits.resize(n);  // Resize the vector to hold all digits
    for (int i = n - 1; i >= 0; i--) {
        if (!isdigit(s[i]))
            throw("INVALID NUMBER");
        a.digits[n - i - 1] = s[i] - '0';  // Convert char to int
    }
    return in; //After processing the input string, the function returns the input stream (in), allowing for further chaining of input operations.
}


/*
This operator<< function overload writes a BigInt to an output stream (ostream), displaying the number in its correct order (from the most significant to the least significant digit).*/
ostream &operator<<(ostream &out,const BigInt &a){
	for (int i = a.digits.size() - 1; i >= 0;i--)
		cout << (short)a.digits[i];/*Each element of a.digits is cast to short before being printed. This cast ensures that even if the internal storage of digits is an integer type (like char or int), it will be displayed as a single digit.*/
	return cout;//The function returns the output stream (cout), allowing for further chaining of output operations.
}


//Driver code with some examples
int main()
{
	BigInt first("12345");
	cout << "The number of digits"
		<< " in first big integer = "
		<< Length(first) << '\n';
	BigInt second(12345);
	if (first == second) {//call == function 
		cout << "first and second are equal!\n";
	}
	else
		cout << "Not equal!\n";
	BigInt third("10000");
	BigInt fourth("100000");
	if (third < fourth) { //call < function
		cout << "third is smaller than fourth!\n";
	}
	BigInt fifth("10000000");
	if (fifth > fourth) { //call > function
		cout << "fifth is larger than fourth!\n";
	}

	// Printing all the numbers
	cout << "first = " << first << '\n';
	cout << "second = " << second << '\n';
	cout << "third = " << third << '\n';
	cout << "fourth = " << fourth<< '\n';
	cout << "fifth = " << fifth<< '\n';

	// Incrementing the value of first
	first++;
	cout << "After incrementing the"
		<< " value of first is : ";
	cout << first << '\n';
	BigInt sum;
	sum = (fourth + fifth);
	cout << "Sum of fourth and fifth = "
		<< sum << '\n';
	BigInt product;
	product = second * third;
	cout << "Product of second and third = "
		<< product << '\n';

	// Print the fibonacci number from 1 to 100
	cout << "-------------------------Fibonacci"
		<< "------------------------------\n";
	for (int i = 0; i <= 100; i++) {
		BigInt Fib;
		Fib = NthFibonacci(i);
		cout << "Fibonacci " << i << " = " << Fib<<'\n';
	}
	cout << "-------------------------Catalan"
		<< "------------------------------\n";
	for (int i = 0; i <= 100; i++) {
		BigInt Cat;
		Cat = NthCatalan(i);
		cout << "Catalan " << i << " = " << Cat<<'\n';
	}

	// Calculating factorial of from 1 to 100
	cout << "-------------------------Factorial"
		<< "------------------------------\n";
	for (int i = 0; i <= 100; i++) {
		BigInt fact;
		fact = Factorial(i);
		cout << "Factorial of "
			<< i << " = ";
		cout << fact << '\n';
	}

}
