/*
Уредување на дом Problem 1 (5 / 8) 
Во оваа задача е потребно да уредите даден дом со маси. Креирајте класа Masa со следниве атрибути:

должина (целобројна вредност)
ширина (целобројна вредност)
конструктор со и без параметри и метода pecati().

Креирајте класа Soba која содржи:

маса (објект од класата Маса)
должина на собата (целобројна вредност)
ширина на собата (целобројна вредност)
конструктор со и без параметри и метода pecati() во која се повикува и pecati() за објектот Masa.

Креирајте класа Kukja со атрибути:

соба (објект од класата Soba)
адреса (низа од 50 знаци), и соодветни методи.
конструктор со и без параметри, деструктор и метода pecati() во која се повикува и pecati() за објектот Soba.

100%
*/

//vasiot kod ovde
#include <iostream>
#include <cstring>

using namespace std;

class Masa {
private:
    int masaSirina;
    int masaDolzina;
public:
    Masa(){}
    
    Masa(int masaSirina, int masaDolzina){
    	this->masaSirina = masaSirina;
        this->masaDolzina = masaDolzina;
    }
    
    void pecati(){
    cout << " Masa: " << masaSirina << " " << masaDolzina << endl;
    }
};

class Soba {
private:
    Masa masa;
    int sobaSirina;
    int sobaDolzina;
public:
    Soba(){}
    
    Soba(int sobaSirina, int sobaDolzina, Masa masa){
    	this->sobaSirina = sobaSirina;
        this->sobaDolzina = sobaDolzina;
        this->masa = masa;
    }
    
    void pecati(){
        cout << " Soba: " << sobaSirina << " " << sobaDolzina;
    	masa.pecati();
    }
};

class Kukja {
private:
    Soba soba;
    char adresa[50];
public:
    Kukja(){}
    
    Kukja(Soba soba, const char *adresa){
        this->soba = soba;
        strcpy(this->adresa, adresa);
    }
    
    ~Kukja(){}
    
    void pecati(){
        cout << "Adresa: " << adresa;
    	soba.pecati();
    }
};


//ne smee da se menuva main funkcijata!
int main(){
    int n;
    cin>>n;
    for(int i=0;i<n;i++){
    	int masaSirina,masaDolzina;
        cin>>masaSirina;
        cin>>masaDolzina;
    	Masa m(masaSirina,masaDolzina);
    	int sobaSirina,sobaDolzina;
        cin>>sobaSirina;
        cin>>sobaDolzina;
    	Soba s(sobaSirina,sobaDolzina,m);
    	char adresa[30];
        cin>>adresa;
    	Kukja k(s,adresa);
    	k.pecati();
	}
    
    return 0;
}