/*
Броеви Problem 5 (6 / 16) 
Да се креира класа PositiveIntegers во која што ќе се чуваат информации за:

низа од позитивни броеви (>0) (динамички алоцирана низа од цели броеви)
број на елементи во низата
максимален капацитет на низата
За класата да се имплементираат:

потребниот конструктор (погледнете во главната функција како се креира објект од оваа класа)
метод void increaseCapacity(int c) којшто го зголемува максималниот капацитет на низата за бројот с
оператор за додавање на нов број во низата од позитивни броеви +=
број се додава ако и само ако
оператор за множење * за множење на низата со друг цел број
Пример, низата има објекти (1 2 3 4 5) и истата се множи со 2, резултатот ќе биде (1 2 3 4 5)*2 = (2 3 6 8 10)
оператор за делење \ за делење на низата до друг цел број
потребно е секој елемент од низата да биде делив со тој број, како и делителот не смее да биде нула.
оператор [] за пристап до елемент од низата
Потребно е да се дефинираат класи за исклучоци и секој од нив да има метод void message() којшто ќе принта соодветна порака кога исклучокот ќе биде фатен. Можните исклучоци се следните:

ArithmeticException (се фрла ако се проба да се дели со нула)
принта порака Division by zero is not allowed
NumbersNotDivisibleException (се фрла ако се проба да се дели низата со некој број, а барем еден елемент од низата не е делив со тој број)
принта порака Division by number [делителот] is not supported
ArrayFullException (се фрла ако се проба да се додади елемент во низа која и е исполнет максималниот капацитет)
принта порака The array is full. Increase the capacity
IndexOutOfBoundsException (се фрла доколку се проба да се пристапи до елемент од низата со несоодветен индекс)
принта порака Index [индексот] is out of bounds
NumberIsNotPositiveException (се фрла доколку се проба да се внесе во низата број што не е позитивен или е нула)
принта порака Number [бројот] is not positive integer.

100%
*/

#include <iostream>

using namespace std;

class ArithmeticException{
public:
    void message(){
    	cout<<"Division by zero is not allowed"<<endl;
    }
};

class NumbersNotDivisibleException{
private:
    int divisor;
public:
    NumbersNotDivisibleException(int divisor){
    	this->divisor = divisor;
    }
    
    void message(){
    	cout<<"Division by "<<divisor<<" is not supported"<<endl;
    }
};

class ArrayFullException{
public:
    void message(){
    	cout<<"The array is full. Increase the capacity"<<endl;
    }
};

class IndexOutOfBoundsException{
private:
    int index;
public:
    IndexOutOfBoundsException(int index){
    	this->index = index;
    }
    
    void message(){
    	cout<<"Index "<<index<<" is out of bounds"<<endl;
    }
};

class NumberIsNotPositiveException{
private:
    int num;
public:
    NumberIsNotPositiveException(int num){
    	this->num = num;
    }
    
    void message(){
    	cout<<"Number "<<num<<" is not positive integer"<<endl;
    }
};

class PositiveIntegers {
private:
    int* nums;
    int numCount;
    int capacity;
public:
    PositiveIntegers(int capacity = 0){
    	this->capacity = capacity;
        this->nums = new int[capacity];
        this->numCount = 0;
    }
    
    void copyConstructor(const PositiveIntegers &pi){
    	this->capacity = pi.capacity;
        this->nums = new int[pi.capacity];
        this->numCount = pi.numCount;
        
        for(int i = 0; i < pi.numCount; i++){
        	this->nums[i] = pi.nums[i];
        }
    }
    
    PositiveIntegers(const PositiveIntegers &pi){
    	copyConstructor(pi);
    }
    
    PositiveIntegers &operator=(const PositiveIntegers &pi){
        if(this!=&pi){
        	delete[] nums;
            copyConstructor(pi);
        }
        
        return *this;
    }
    
    PositiveIntegers &operator+=(int newNum){
        //ARRAY FULL EXCEPTION
        if(numCount == capacity){
        	throw ArrayFullException();
        }
        //NUM < 0 EXCEPTION
        if(newNum <= 0){
        	throw NumberIsNotPositiveException(newNum);
        }
        
    	nums[numCount++] = newNum;
        
        return *this;
    }
    
    PositiveIntegers operator*(int multiplier){
        PositiveIntegers pi(*this);
        
        for(int i = 0; i < pi.numCount; i++){
        	pi.nums[i] *= multiplier;
        }
        
        return pi;
    }
    
    PositiveIntegers operator/(int divisor){
        //DIVIDE BY 0 EXCEPTION
        if(divisor == 0){
        	throw ArithmeticException();
        }
        
        for(int i = 0; i < this->numCount; i++){
            //NOT DIVISIBLE EXCEPTION
            if(nums[i]%divisor != 0){
            	throw NumbersNotDivisibleException(divisor);
            }
        }
        
        PositiveIntegers pi(*this);
        
        for(int i = 0; i < pi.numCount; i++){
        	pi.nums[i] /= divisor;
        }
        
        return pi;
    }
    
    int &operator[](int i){
        //INDEX OOB EXCEPTION
        if(i<0 || i>numCount){
        	throw IndexOutOfBoundsException(i);	
        }
        
    	return nums[i];
    }
    
    void increaseCapacity(int c){
    	int *temp = new int[capacity+c];
        for(int i = 0; i < numCount; i++){
        	temp[i] = nums[i];
        }
        
        delete[] nums;
        nums = temp;
        capacity += c;
    }
    
    void print(){
    	cout<<"Size: "<<numCount<<" Capacity: "<<capacity<<" Numbers: ";
        
        for(int i = 0; i < numCount; i++){
        	cout<<nums[i]<<" ";
        }
        
        cout<<endl;
    }
    
};

int main() {
	
	int n,capacity;
	cin >> n >> capacity;
	PositiveIntegers pi (capacity);
    
    
	for (int i=0;i<n;i++){
		int number;
		cin>>number;
        
        try{
			pi+=number;
        }
        catch(ArrayFullException &err){
        	err.message();
        }
        catch(NumberIsNotPositiveException &err){
        	err.message();
        }
        
	}
	cout<<"===FIRST ATTEMPT TO ADD NUMBERS==="<<endl;
	pi.print();
	int incCapacity;
	cin>>incCapacity;
	pi.increaseCapacity(incCapacity);
	cout<<"===INCREASING CAPACITY==="<<endl;
	pi.print();
	
	int n1;
	cin>>n1;
	for (int i=0;i<n1;i++){
		int number;
		cin>>number;
		
		try{
			pi+=number;
        }
        catch(ArrayFullException &err){
        	err.message();
        }
        catch(NumberIsNotPositiveException &err){
        	err.message();
        }
        
	}
	cout<<"===SECOND ATTEMPT TO ADD NUMBERS==="<<endl;
	
    pi.print();	
	PositiveIntegers pi1;
	
	cout<<"===TESTING DIVISION==="<<endl;	
	
    try{
		pi1 = pi/0;
		pi1.print();
    }
    catch(ArithmeticException &err){
    	err.message();
    }
    catch(NumbersNotDivisibleException &err){
    	err.message();
    }
	
    try{
		pi1 = pi/1;
		pi1.print();
    }
    catch(ArithmeticException &err){
    	err.message();
    }
    catch(NumbersNotDivisibleException &err){
    	err.message();
    }
    
    try{
		pi1 = pi/2;
		pi1.print();
    }
    catch(ArithmeticException &err){
    	err.message();
    }
    catch(NumbersNotDivisibleException &err){
    	err.message();
    }
	
	cout<<"===TESTING MULTIPLICATION==="<<endl;
	pi1 = pi*3;
	pi1.print();
	
	
	cout<<"===TESTING [] ==="<<endl;
    
    try{
		cout<<"PositiveIntegers[-1] = "<<pi[-1]<<endl;	
    }
    catch(IndexOutOfBoundsException &err){
    	err.message();
    }
	
    try{
		cout<<"PositiveIntegers[2] = "<<pi[2]<<endl;	
    }
    catch(IndexOutOfBoundsException &err){
    	err.message();
    }
    
    try{
		cout<<"PositiveIntegers[3] = "<<pi[3]<<endl;	
    }
    catch(IndexOutOfBoundsException &err){
    	err.message();
    }
    
    try{
		cout<<"PositiveIntegers[12] = "<<pi[12]<<endl;	
    }
    catch(IndexOutOfBoundsException &err){
    	err.message();
    }
	
	
	
	
	return 0;
}