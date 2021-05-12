/*
Квадрат и правоаголник Problem 4 (7 / 15) 
Да се дефинира класата Kvadrat во која што се чува информација за:

должината на страната а на квадратот (double)
За класата да се дефинираат:

default конструктор
конструктор со аргументи
copy конструктор
double perimetar () што пресметува периметар на квадратот
double plostina () што пресметува плоштина на квадратот
void pecati () што печати информации за квадратот како во тест примерите
Да се имплементира класа Pravoagolnik што наследува од класата Kvadrat. Во неа се чуваат дополнителни информации за:

проширувањето x на двете паралелни страни на квадратот (double)
проширувањето у на другите две паралелни страни (double)
Правоаголникот всушност сега ќе има 2 страни со должина a+x и две страни со должина a+y.

За класата да се дефинираат:

default конструктор
конструктор Pravoagolnik (const Kvadrat &k, double x, double y)
copy конструктор
Да се препокријат трите методи дефинирани погоре за класата Kvadrat.

Напомени:

Ако x и y се исти, тогаш формата не е правоаголник туку е повторно квадрат. Во тој случај pecati() се повикува исто како за квадрат.
При препокривање на методите во класата Pravoagolnik мора да има повик кон истоимените методи од класата Kvadrat

100%
*/

#include <iostream>

using namespace std;

class Kvadrat {
    protected:
    	double a;
    public:
    Kvadrat(){}

    Kvadrat(double a){
    	this->a = a;
    }

    Kvadrat(const Kvadrat &kvadrat){
    	this->a = kvadrat.a;
    }
   
    double perimetar(){
    	return 4*a;
    }
    
    double plostina(){
    	return a*a;
    }
   
    void pecati(){
    	cout << "Kvadrat so dolzina a="<< a <<" ima plostina P="<< plostina() <<" i perimetar L="<< perimetar() << endl;
    }
};

class Pravoagolnik : public Kvadrat{ 
    private:
    	double x;
    	double y;
    public:
    	Pravoagolnik(){} 
    
    	Pravoagolnik(const Kvadrat &k, double x, double y) : Kvadrat(k){
    		this->x = a+x;
            this->y = a+y;
    	}
   
    	Pravoagolnik(const Pravoagolnik &p){ 
			this->x = a+p.x;
            this->y = a+p.y;
    	}
    
    	double perimetar(){
            //if(x==y) return Kvadrat::perimetar();
            return 2*x + 2*y;
        }
    
    	double plostina(){
    		//if(x==y) return Kvadrat::plostina();
            return x*y;
        }
    
    	void pecati(){
            if(x==y){
            	cout << "Kvadrat so dolzina a="<< x <<" ima plostina P="<< plostina() <<" i perimetar L="<< perimetar() << endl;
            } else {
            	cout<<"Pravoagolnik so strani: "<<x<<" i "<<y<<" ima plostina P="<<plostina()<<" i perimetar L="<<perimetar()<<endl;
            }
    	}
};

int main() {
	int n;
    double a,x,y;
	Kvadrat * kvadrati;
	Pravoagolnik * pravoagolnici;
	
	cin>>n;
    
    kvadrati = new Kvadrat [n];
    pravoagolnici = new Pravoagolnik [n];
    
	for (int i=0;i<n;i++){
		cin>>a;
        
		kvadrati[i] = Kvadrat(a);
	}
	
	for (int i=0;i<n;i++){
		cin>>x>>y;
        
		pravoagolnici[i]=Pravoagolnik(kvadrati[i],x,y);
	}
	
	int testCase;
	cin>>testCase;
    
	if (testCase==1){
		cout<<"===Testiranje na klasata Kvadrat==="<<endl;
		for (int i=0;i<n;i++)
			kvadrati[i].pecati();
	}
	else {
		cout<<"===Testiranje na klasata Pravoagolnik==="<<endl;
		for (int i=0;i<n;i++)
			pravoagolnici[i].pecati();
	}
}