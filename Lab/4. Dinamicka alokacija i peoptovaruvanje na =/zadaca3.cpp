/*
Задача 3 Problem 3 (1 / 3) 
Да се дефинира класа Pica за која ќе се чуваат податоци за:

име на пицата (низа од 15 знаци)
цена (цел број)
состојки (динамички алоцирана низа од знаци)
намалување на цената во проценти (цел број) - ако пицата не е на промоција намалувањето има вредност нула, во спротивно, вредност поголема од нула и не поголема од 100.
За потребите на оваа класа да се креираат потребните конструктори и да се напише соодветен деструктор. Дополнително за оваа класа да се дефинира функцијата:

pecati() - функција во која ќе се печатат податоците за пицата во следниот формат: име - состојки, цена.
istiSe(Pica p) - функција за споредба на две пици според состојките :
Да се дефинира класа Picerija во која се чуваат:

име (низа од максимум 15 знаци)
динмички алоцирана низа од објекти од класата Pica
број на пици (цел број)
За потребите на оваа класа да се дефинираат потребните конструктори и да се напише соодветен деструктор. Да се имплементираат и следниве методи:

dodadi (Pica P) - за додавање нова пица во пицеријата, но само ако не постои иста во низата (нема пица со исти состојки со пицата што треба да се додаде).
void piciNaPromocija() - се печатат сите пици од пицеријата што се на промоција во формат : име - состојки, цена, цена со попуст.

100%
*/

#include <iostream>
#include <cstring>

using namespace std;

//Vasiot kod tuka
class Pica{
private:
    char ime[15];
    int cena;
    char *sostojki;
    int popust;
public:
    Pica(const char *ime = "", int cena = 0, const char *sostojki = "", int popust = 0){
    	strcpy(this->ime, ime);
        this->cena = cena;
        this->popust = popust;
        this->sostojki = new char[strlen(sostojki)+1];
        strcpy(this->sostojki, sostojki);
    }
    // copy constructor??
    Pica(const Pica &p){
    	strcpy(this->ime, p.ime);
        this->cena = p.cena;
        this->popust = p.popust;
        this->sostojki = new char[strlen(p.sostojki)+1];
        strcpy(this->sostojki, p.sostojki);
    }
    
    Pica &operator = (const Pica &pica){
        if(this!=&pica){
        	delete[] sostojki;
            this->cena = pica.cena;
            this->popust = pica.popust;
            this->sostojki = new char[strlen(pica.sostojki)+1];
            strcpy(this->sostojki, pica.sostojki);
            strcpy(this->ime, pica.ime);
            
        }
        return *this;
    }
    
    int getCena(){
    	return cena;
    }
    
    int getPopust(){
    	return popust;
    }
    
    void pecati(){
    	cout << ime << " - " << sostojki << ", " << cena;
    }
    
    bool istiSe(Pica p){
    	return !strcmp(sostojki, p.sostojki);
    }
    
    ~Pica(){
    	delete[] sostojki;
    }
};

class Picerija{
private:
	char ime[15];
    Pica *pici;
    int brojPici;
public:
    Picerija(const char *ime = "", int brojPici = 0, Pica *pici = 0){
    	this->brojPici = brojPici;
        this->pici = new Pica[brojPici];
        strcpy(this->ime, ime);
        for(int i = 0; i < brojPici; i++){
        	this->pici[i] = pici[i];
        }
    }
    
    Picerija(const Picerija &p){
    	this->brojPici = p.brojPici;
        this->pici = new Pica[p.brojPici];
        strcpy(this->ime, p.ime);
        for(int i = 0; i < brojPici; i++){
        	this->pici[i] = p.pici[i];
        }
    }
    
    Picerija &operator= (const Picerija &picerija){
        if(this!=&picerija){
        	delete[] this->pici;
            pici = new Pica[brojPici];
            for(int i = 0; i < brojPici; i++){
            	pici[i] = picerija.pici[i];
            }
            brojPici = picerija.brojPici;
            strcpy(ime, picerija.ime);
        }
        return *this;
    }
    
    char *getIme(){
    	return ime;
    }
    
    void setIme(const char *ime){
    	strcpy(this->ime, ime);
    }
    
    void dodadi(Pica p){
    	bool isti = false;
        for(int i = 0; i < brojPici; i++){
            if(pici[i].istiSe(p)){
            	isti = true;
            }
        }
        if(!isti){
        	Pica *noviPici = new Pica[brojPici + 1];
            for(int i = 0; i < brojPici; i++){
            	noviPici[i] = pici[i];
            }
            noviPici[brojPici++] = p;
            delete[] pici;
            pici = noviPici;
        }
    }
    
    void piciNaPromocija(){
        for(int i = 0; i < brojPici; i++){
            if(pici[i].getPopust()){
            	pici[i].pecati();
                cout << " " << pici[i].getCena() * (1 - (pici[i].getPopust()/100.0)) << endl;
            }
        }
    }
    
    ~Picerija(){
    	delete[] pici;
    }
};

int main () {

    int n;
    char ime[15];
    cin >> ime;
    cin >> n;

    Picerija p1(ime);
    for(int i = 0; i < n; i++){
        char imp[100];
        cin.get();
        cin.getline(imp,100);
        int cena;
        cin >> cena;
        char sostojki[100];
        cin.get();
        cin.getline(sostojki,100);
        int popust;
        cin >> popust;
        Pica p(imp,cena,sostojki,popust);
        p1.dodadi(p);
    }

    Picerija p2 = p1;
    cin >> ime;
    p2.setIme(ime);
    char imp[100];
    cin.get();
    cin.getline(imp,100);
    int cena;
    cin >> cena;
    char sostojki[100];
    cin.get();
    cin.getline(sostojki,100);
    int popust;
    cin >> popust;
    Pica p(imp,cena,sostojki,popust);
    p2.dodadi(p);

    cout<<p1.getIme()<<endl;
    cout<<"Pici na promocija:"<<endl;
    p1.piciNaPromocija();

    cout<<p2.getIme()<<endl;
    cout<<"Pici na promocija:"<<endl;
    p2.piciNaPromocija();

	return 0;
}
