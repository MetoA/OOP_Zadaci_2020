/*
Воз Problem 8 (1 / 7)
(40 поени)

Да се креира класа Patnik во која се чуваат податоци за патниците на еден воз и тоа: име (низа од максимум 100 знаци), класа на вагон во која се вози (цел број 1 или 2) и велосипед (булова променлива).

За оваа класа да се преоптоварат:

Оператор << - за печатење на информациите за патникот во формат:
Име на патник

Бројот на класата (1 или 2)

Дали има велосипед?

Потоа да се креира клaса Voz во која се чува: крајна дестинација (низа од максимум 100 знаци), динамички алоцирана низа од објекти од класата Patnik, како и број на елементи во низата (цел број), број на дозволени велосипеди (цел број).

За класата да се обезбедат:

Оператор += – за додавање нов патник во воз. Патник со велосипед ќе може да се качи во воз само ако возот го дозволува тоа.
Оператор << - за печатење на крајната дестинација до која вози и листата на патници
Функција со потпис: patniciNemaMesto(). Со оваа функција се пресметува вкупниот број на патници (од 1-ва класа и 2-ра класа) за кои нема место да влезат во возот со велосипед. Притоа треба да се внимава дека во пресметувањето на вкупниот број патници со велосипеди кои ќе влезат во возот прво треба да се земат предвид патниците од 1-ва класа, а потоа се дозволува да влегуваат патниците од 2-ра класа се додека не се достигне максималниот број на дозволени велосипеди во возот. На крај се печати бројот на патници со велосипеди кои остануваат (не влегуваат во возот) од 1-ва класа, а потоа од 2-ра класа.

100%
*/

#include<iostream>
#include<cstring>
using namespace std;

class Patnik{

private:
    char ime[100];
    int klasa;
    bool velosiped;
	
public:
    Patnik(char ime[100] = "", int klasa = 0, bool velosiped = false){
    	strcpy(this->ime, ime);
        this->klasa = klasa;
        this->velosiped = velosiped;
    }
    
    friend ostream &operator<<(ostream &stream, const Patnik &p){
    	stream<<p.ime<<endl;
        stream<<p.klasa<<endl;
        stream<<p.velosiped<<endl;
        
        return stream;
    }
    
    bool hasVelosiped(){
    	return velosiped;
    }
    
    int getKlasa(){
    	return klasa;
    }
	
};

class Voz{

private:
    char destinacija[100];
    Patnik *patnici;
    int brElem;
    int dozvoleniVelosipedi;
	
public:
    Voz(char destinacija[100], int dozvoleniVelosipedi){
    	strcpy(this->destinacija, destinacija);
        this->dozvoleniVelosipedi = dozvoleniVelosipedi;
        brElem = 0;
        patnici = new Patnik[brElem];
    }
    
    
    
    Voz &operator+=(Patnik p){
    	Patnik *temp = new Patnik[brElem+1];
        
        for(int i = 0; i < brElem; ++i){
        	temp[i] = patnici[i];
        }
        
        temp[brElem++] = p;
        
        delete[] patnici;
        
        patnici = temp;
        
        return *this;
    }
    
    void patniciNemaMesto(){
    	
    }
    
    friend ostream &operator<<(ostream &stream, const Voz &v){
    	stream<<v.destinacija<<endl;
        if(!v.dozvoleniVelosipedi){
        	for(int i = 0; i < v.brElem; i++){
                if(!(v.patnici[i].hasVelosiped())){
                	stream<<v.patnici[i]<<endl;
                }
            }
            
            stream<<"Brojot na patnici od 1-va klasa koi ostanale bez mesto e: 0"<<endl;
			stream<<"Brojot na patnici od 2-ra klasa koi ostanale bez mesto e: 0"<<endl;
        } else {
        	int classOneHasBike = 0;
            int classOneNoSpace = 0;
            int classTwoHasBike = 0;
            int classTwoNoSpace = 0;
            
            for(int i = 0; i < v.brElem; ++i){
                stream<<v.patnici[i]<<endl;
                
                if(v.patnici[i].hasVelosiped()){
                    if(v.patnici[i].getKlasa() == 1){
                    	classOneHasBike++;
                    } else {
                    	classTwoHasBike++;
                    }
                }
            }
            
            if(classOneHasBike > v.dozvoleniVelosipedi){
            	classOneNoSpace = classOneHasBike - v.dozvoleniVelosipedi;
                classTwoNoSpace = classTwoHasBike;
            } else {
            	classOneNoSpace = 0;
                if(classOneHasBike + classTwoHasBike > v.dozvoleniVelosipedi){
                	classTwoNoSpace = classOneHasBike + classTwoHasBike - v.dozvoleniVelosipedi;
                } else {
                	classTwoNoSpace = 0;
                }
            }
            
            stream<<"Brojot na patnici od 1-va klasa koi ostanale bez mesto e: "<<classOneNoSpace <<endl;
			stream<<"Brojot na patnici od 2-ra klasa koi ostanale bez mesto e: "<<classTwoNoSpace <<endl;
        }
        
        return stream;
    }
	
};


int main()
{
	Patnik p;
	char ime[100], destinacija[100];
	int n;
	bool velosiped;
	int klasa;
	int maxv;
	cin >> destinacija >> maxv;
	cin >> n;
	Voz v(destinacija, maxv);
	//cout<<v<<endl;
	for (int i = 0; i < n; i++){
		cin >> ime >> klasa >> velosiped;
		Patnik p(ime, klasa, velosiped);
		//cout<<p<<endl;
		v += p;
	}
	cout << v;
	v.patniciNemaMesto();

	return 0;
}
