/*
Спортски екипи Problem 2 (1 / 1) 
Да се дефинира класа Ekipa за коjа се чуваат следниве информации:

името на екипата (низа од наjмногу 15 знаци)
броj на порази
броj на победи
За оваа класа да се дефинира метод pecati() коjа ги печати податоците за екипаta. Од оваа класа да се изведe новa класa, FudbalskaEkipa.

За фудбалската екипа дополнително се чуваат информации за:

вкупниот броj на црвени картони
вкупниот броj жолти картони
броjот на нерешени натпревари
За фудбалската екипа да се преоптовари методот pecati(), така што покрај останатите информации, ќе се испечатат и бројот на нерешени резултати и вкупен број на поени во 
формат: Име на екипа, броj на победи, броj на порази, броj на нерешени натпревари и вкупен броj на поени (за победа фудбалската екипа добива 3 поени, додека за нерешен резултата, 1 поен); 

100%
*/

//Vasiot kod ovde
#include <iostream> 
#include <cstring>

using namespace std;

class Ekipa{
protected:
    char ime[15];
    int pobedi;
    int porazi;
public:
    Ekipa(char *ime = "", int pobedi = 0, int porazi = 0){
    	strcpy(this->ime, ime);
        this->pobedi = pobedi;
        this->porazi = porazi;
    }
    
    ~Ekipa(){}
    
    void pecati(){
    	cout << "Ime: " << ime << " Pobedi: " << pobedi << " Porazi: " << porazi;
    }
};

class FudbalskaEkipa : public Ekipa{
private:
    int crveniKartoni;
    int zoltiKartoni;
    int brojNereseni;
public:
    FudbalskaEkipa(char *ime = "", int pobedi = 0, int porazi = 0, int crveniKartoni = 0, int zoltiKartoni = 0, int brojNereseni = 0)
    : Ekipa(ime, pobedi, porazi){
        this->crveniKartoni = crveniKartoni;
        this->zoltiKartoni = zoltiKartoni;
        this->brojNereseni = brojNereseni;
    }
    
    void pecati(){
		Ekipa::pecati();
        cout << " Nereseni: " << brojNereseni << " Poeni: " << pobedi*3 + brojNereseni << endl;
    }
};

int main(){
	char ime[15];
	int pob,por,ck,zk,ner;
	cin>>ime>>pob>>por>>ck>>zk>>ner;
	FudbalskaEkipa f1(ime,pob,por,ck,zk,ner);
	f1.pecati();
	return 0;
}