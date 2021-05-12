/*
Возач Problem 3 (14 / 22)
Да се дефинира класа Vozac во која се чуваат информации за:

име (низа од максимум 100 знаци)
возраст (цел број)
број на трки (цел број)
дали е ветеран (да/не).
Да се преоптоварат:

операторот << за печатење кој ќе ги печати името, возраст, бројот на трки и дали е ветеран (се печати VETERAN)
операторот == за споредување на два возачи според заработувачката по трка.
Од оваа класа да се изведат две нови класи Avtomobilist и Motociklist.

За автомобилистот дополнително се чува:

цена на автомобилот (децимален број).
За мотоциклистот дополнително се чува:

моќност на мотор (цел број).
Заработувачката по трка на возачите се пресметува како:

за автомобилостот заработувачката по трка е CENAAVTOMOBIL/5
за мотоциклистот заработувачката по трка е MOKJNOSTNAMOTOR∗20
Секој автомобилист плаќа данок на заработка. Да се напишат соодветни методи за пресметување данок:

за автомобилисти: ако бројот на трки е поголем од 10 стапката на данок е 15% од заработката, инаку 10% од заработката.
за мотоциклисти: ако е ветеран стапката на данок е 25% од заработката, инаку 20% од заработката.
Да се напше надворешна функција soIstaZarabotuvachka која како аргументи прима низа од покажувачи од класата Vocac, нивниот број, како и покажувач кон ојбект од возач и враќа како резултат бројот на возачи кои имаат иста заработувачка по трка со проследениот возач.

100%
*/

#include <iostream>
#include <cstring>

using namespace std;

class Vozac{
protected:
  char ime[100];
  int vozrast;
  int brTrki;
  bool isVeteran;
public:
  Vozac(char *ime = "", int vozrast = 0, int brTrki = 0, bool isVeteran = false){
    strcpy(this->ime, ime);
    this->vozrast = vozrast;
    this->brTrki = brTrki;
    this->isVeteran = isVeteran;
  }

  virtual double zarabotuvachkaPoTrka() const{
    return 1;
  }

  virtual double danok(){
    return 1;
  }
    
    bool operator==(const Vozac &v){
    	return (zarabotuvachkaPoTrka() == v.zarabotuvachkaPoTrka());
    }

  friend ostream &operator<<(ostream &stream, const Vozac &v){
    stream<<v.ime<<endl;
    stream<<v.vozrast<<endl;
    stream<<v.brTrki<<endl;

    if(v.isVeteran) stream<<"VETERAN"<<endl;

    return stream;
  }
};

class Avtomobilist : public Vozac{
private:
  double cena;
public:
  Avtomobilist(char *ime = "", int vozrast = 0, int brTrki = 0, bool isVeteran = false, double cena = 0):Vozac(ime, vozrast, brTrki, isVeteran){
    this->cena = cena;
  }

  double zarabotuvachkaPoTrka() const{
    return cena/5;
  }

  double danok(){
    if(brTrki > 10) return zarabotuvachkaPoTrka() * 0.15;
    return zarabotuvachkaPoTrka() * 0.1;
  }
};

class Motociklist : public Vozac{
private:
  int mokjnost;
public:
  Motociklist(char *ime = "", int vozrast = 0, int brTrki = 0, bool isVeteran = false, int mokjnost = 0):Vozac(ime, vozrast, brTrki, isVeteran){
    this->mokjnost = mokjnost;
  }

  double zarabotuvachkaPoTrka() const{
    return mokjnost * 20;
  }

  double danok(){
    if(isVeteran) return zarabotuvachkaPoTrka() * 0.25;
    return zarabotuvachkaPoTrka() * 0.2;
  }
};

int soIstaZarabotuvachka(Vozac **vozaci, int n, Vozac *v){
  int broj = 0;

  for(int i = 0; i < n; i++){
    if(vozaci[i]->zarabotuvachkaPoTrka() == v->zarabotuvachkaPoTrka()) broj++;
  }

  return broj;
}

// vashiot kod ovde

int main() {
	int n, x;
	cin >> n >> x;
	Vozac **v = new Vozac*[n];
	char ime[100];
	int vozrast;
	int trki;
	bool vet;
	for(int i = 0; i < n; ++i) {
		cin >> ime >> vozrast >> trki >> vet;
		if(i < x) {
			float cena_avto;
			cin >> cena_avto;
			v[i] = new Avtomobilist(ime, vozrast, trki, vet, cena_avto);
		} else {
			int mokjnost;
			cin >> mokjnost;
			v[i] = new Motociklist(ime, vozrast, trki, vet, mokjnost);
		}
	}
	cout << "=== DANOK ===" << endl;
	for(int i = 0; i < n; ++i) {
		cout << *v[i];
		cout << v[i]->danok() << endl;
	}
	cin >> ime >> vozrast >> trki >> vet;
	int mokjnost;
	cin >> mokjnost;
	Vozac *vx = new Motociklist(ime, vozrast, trki, vet, mokjnost);
	cout << "=== VOZAC X ===" << endl;
	cout << *vx;
	cout << "=== SO ISTA ZARABOTUVACKA KAKO VOZAC X ===" << endl;
	cout << soIstaZarabotuvachka(v, n, vx);
    for(int i = 0; i < n; ++i) {
        delete v[i];
    }
    delete [] v;
    delete vx;
	return 0;
}