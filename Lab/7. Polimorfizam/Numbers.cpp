/*
Numbers Problem 4 (2 / 7) 
Да се дефинира апстрктна класа Number со следните чисто виртуелни методи:

double doubleValue() -ја враќа децималната вредност на даден број
int intValue()- ја враќа целобројната вредност на даден број
void print() - печати информации за бројот. (1 поен)
Од оваа класа да се изведат две класи:

Integer (во која што се чува еден број од тип int)
Double (во која што се чува еден број од тип double) (1 поен).
За двете изведени класи да се имплементираaт соодветен конструктори, како и да се препокријат методите од основната класа. (1 поени)

Да се преоптовари операторот == којшто ќе споредува два броеви според нивната вредност (објекти од класа Number) (1 поен)

Дополнително да се дефинира класа Numbers во која што ќе се чуваат:

динамички алоцирана низа од покажувачи кон објекти од класата Number
број на елементи во низата од покажувачи
За класата да се имплементира соодветен конструктор (default) , како и: (1 поени)

операторот += за додавање на броеви во низата од броеви (1 поен)
Бројот се додава ако и само ако сите броеви што се веќе додадени во низата се различни од него
функција void statistics() која што печати информации за броевите во низата: (2 поени)
Count of numbers: [број на броеви во низата

Sum of all numbers: [сума на сите броеви во низата]

Count of integer numbers: [број на цели броеви (Integer)]

Sum of integer numbers: [сума на сите цели броеви (Integer)]

Count of double numbers: [број на децимални броеви (Double)]

Sum of double numbers: [сума на сите децимални броеви (Double)]

функција void integersLessThan (Integer n) која што ги печати сите цели броеви помали од бројот n (1 поен)
функција void doublesBiggerThan (Double n) која што ги печати сите децимални броеви поголеми од бројот n (1 поен)

100%
*/

#include<iostream>
using namespace std;

class Number {
    public:
    //TODO da se deklariraat trite cisto virtuelni metodi
    virtual double doubleValue() = 0;
    virtual int intValue() = 0;
    virtual void print() = 0;
    
    bool operator==(Number &one){
		return(one.doubleValue() == this->doubleValue());
	}
}; 

//ТODO preoptovaruvanje na operatorot == 



class Integer : public Number{ //TODO da se dodadi izraz za nasleduvanje od Number
    private:
    //TODO da se deklariraat promenlivite
    	int brojInt;
    public:
    //TODO konstruktor so eden argument
    Integer(int brojInt){
    	this->brojInt = brojInt;
    }
    //TODO da se prepokrijat metodite od klasata Number
    double doubleValue(){
    	return double(brojInt);
    }
    
    int intValue(){
    	return brojInt;
    }
    
    void print(){
    	cout << brojInt << endl;
    }
};

class Double : public Number{ //TODO da se dodadi izraz za nasleduvanje od Number
    private:
    //TODO da se deklariraat promenlivite
    	double brojDouble;
    public:
    //TODO konstruktor so eden argument
    Double(double brojDouble){
    	this->brojDouble = brojDouble;
    }	
    //TODO da se prepokrijat metodite od klasata Number
    double doubleValue(){
    	return brojDouble;
    }
    
    int intValue(){
    	return int(brojDouble);
    }
    
    void print(){
    	cout << brojDouble << endl;
    }
};

class Numbers{
    private:
    //TODO deklariranje na promenlivite
    	Number** broevi;
    	int brojElem;
    public:
    //TODO default konstruktor
    Numbers(){
    	broevi = new Number*[0];
        brojElem = 0;
    }
    //TODO copy konstruktor
    Numbers(const Numbers &nums){
		brojElem = nums.brojElem;
        
        broevi = new Number*[brojElem];
        for(int i = 0; i < brojElem; i++){
			broevi[i] = nums.broevi[i];
        }
    }
    //TODO operator =
    Numbers &operator=(const Numbers &nums){
    	brojElem = nums.brojElem;
        
        broevi = new Number*[brojElem];
        for(int i = 0; i < brojElem; i++){
        	broevi[i] = nums.broevi[i];
        }
        
        return *this;
        
    }
    //TODO destruktor
    ~Numbers(){
    	delete[] broevi;
    }
    //TODO operator += (operatorot da prima pointer od objekt od Number, a ne referenca)
    Numbers &operator+=(Number *num){
		bool add = true;
        
        for(int i = 0; i < brojElem; i++){
            if(*broevi[i] == *num){
            	add = false;
            }
        }
        
        if(add){
        	Number **nova = new Number*[brojElem+1];
            
            for(int i = 0; i < brojElem; i++){
            	nova[i] = broevi[i];
        	}
            
            if(add){
            	nova[brojElem] = num;
                brojElem++;
            }
            
            delete[] broevi;
            broevi = nova;
        }
        
        return *this;
    }
    //TODO void statistics()
    void statistics(){
        double sumAll = 0;
        double sumDouble = 0;
        int intCount = 0;
        int doubleCount = 0;
        int sumInt = 0;
        
        for(int i = 0; i < brojElem; i++){
			sumAll += broevi[i]->doubleValue();
        }
        
        for(int i = 0; i < brojElem; i++){
            if(dynamic_cast<Integer*>(broevi[i])){
				intCount++;
                sumInt += broevi[i]->intValue();            
            }
        }
        
        for(int i = 0; i < brojElem; i++){
			if(dynamic_cast<Double*>(broevi[i])){
				doubleCount++;
                sumDouble += broevi[i]->doubleValue();            
            }
        }
        
		cout << "Count of numbers: " << brojElem << endl;
        cout << "Sum of all numbers: " << sumAll << endl;
        cout << "Count of integer numbers: " << intCount << endl;
        cout << "Sum of integer numbers: " << sumInt << endl;
        cout << "Count of double numbers: " << doubleCount << endl;
        cout << "Sum of double numbers: " << sumDouble << endl;
    }
    
    //TODO void integersLessThan (Integer n)
    void integersLessThan(Integer n){
		bool no = true;
        
        for (int i = 0; i < brojElem; i++){
            if (dynamic_cast<Integer*>(broevi[i])){
                if (broevi[i]->intValue() < n.intValue()){
                    no = false;
                    cout << "Integer: " << broevi[i]->intValue() << endl;
                }
            }
        }
        
        if (no) cout << "None" << endl;
    }
    //TODO void doublesBiggerThan (Double n)
    void doublesBiggerThan(Double n){
		bool no = true;
        
        for (int i = 0; i < brojElem; i++){
            if (dynamic_cast<Double*>(broevi[i])){
                if (broevi[i]->doubleValue() > n.doubleValue()){
                    no = false;
                    cout << "Double: " << broevi[i]->doubleValue() << endl;
                }
            }
        }
        
        if (no) cout << "None" << endl;
    }
};

int main() {
	
	int n;
	cin>>n;
	Numbers numbers;
	for (int i=0;i<n;i++){
		int type;
		double number;
		cin>>type>>number;
		if (type==0){//Integer object
			Integer * integer = new Integer((int) number);
			numbers+=integer;
		}
		else {
			Double * doublee = new Double(number);
			numbers+=doublee;
		}
	}
	
	int lessThan;
	double biggerThan;
	
	cin>>lessThan;
	cin>>biggerThan;		
	
	cout<<"STATISTICS FOR THE NUMBERS\n";
	numbers.statistics();
	cout<<"INTEGER NUMBERS LESS THAN "<<lessThan<<endl;
	numbers.integersLessThan(Integer(lessThan));
	cout<<"DOUBLE NUMBERS BIGGER THAN "<<biggerThan<<endl;
	numbers.doublesBiggerThan(Double(biggerThan));
	
	return 0;
}