/*
Круг Problem 2 (2 / 2) 
Да се дефинира класа Krug, во која се чуваат информации за:

радиус float
бројот π const float.
Во класата да се реализираат:

default конструктор и конструктор со аргументи
метод за пресметување плоштина
метод за пресметување периметар
метод кој кажува дали плоштината и периметарот на даден круг се еднакви

100%
*/

#include <iostream>
using namespace std;

class Krug {
private:
	float radius;
    const float pi = 3.14;
public:
  	Krug(){}
    Krug(float r){
    this->radius = r;
    }
    
    float perimetar(){
    	return 2 * pi * radius;
    }
    
    float plostina(){
    	return pi * radius * radius;
    }
    
    int ednakvi(){
        if(this->perimetar() == this->plostina()){
        	return 1;
        } else {
        	return 0;
        }
    }
};

int main() {
	float r;
	cin >> r;
	//instanciraj objekt od klasata Krug cij radius e vrednosta procitana od tastatura
    Krug k(r);
	cout << k.perimetar() << endl;
	cout << k.plostina() << endl;
	cout << k.ednakvi() <<endl;
    //instanciraj objekt od klasata Krug cij radius ne e definiran
    Krug k1();
	return 0;
}