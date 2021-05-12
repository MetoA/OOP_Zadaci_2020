/*
Жичани инструменти Problem 1 (2 / 2) 
Да се креира хиерархиjа на класи за репрезентациjа на жичани инструменти. За потребите на оваа хиерархиjа да се дефинира класа ZicanInstrument од коjа ќе бидат изведени двете класи Mandolina и Violina.

Во класата ZicanInstrument се чуваат податоци за:

името на инструментот (низа од 20 знаци)
броjот на жици
основната цена на инструментот.
За класата Mandolina дополнително се чува неjзината форма (низа од 20 знаци).

За класата Violina дополнително се чува неjзината големина (децимален броj).

За секоjа изведените класи треба да се дефинираат соодветните конструктори и следните методи:

cena() за пресметување на цената на инструментот
основната цена на мандолината се зголемува за 15% доколку таа има форма во Неаполитански стил (вредноста на променливата форма е “Neapolitan”)
основната цена на виолината се зголемува за 10% ако неjзината големина има вредност 1/4 (0.25), односно за 20% ако неjзината големина има вредност 1 (1.00)
проптоварување на операторот ==, коj ги споредува жичаните инструменти според броjот на жици што го имаат
преоптоварување на операторот << за печатење на сите податоци за жичаните инструменти.
Да се напише функциjа pecatiInstrumenti(ZicanInstrument &zi, ZicanInstrument **i, int n) коjа на влез прима жичан инструмент, низа од покажувачи кон жичани инструменти и 
броj на елементи во низата. Функциjата jа печати цената на сите жичани инструменти од низата кои имаат ист броj на жици како и инструментот проследен како прв аргумент на функциjата.

100%
*/

//Vasiot kod ovde:
#include <iostream>
#include <cstring>

using namespace std;

class ZicanInstrument {
protected:
	char ime[20];
	int brojZici;
	float osnovnaCena;
public:
	ZicanInstrument(char ime[20] = "", int brojZici = 0, float osnovnaCena = 0) {
		strcpy(this->ime, ime);
		this->brojZici = brojZici;
		this->osnovnaCena = osnovnaCena;
	}
    
    virtual int getBrojZici() {
    	return brojZici;
    }
    
    virtual float cena(){
    	return osnovnaCena;	
    }
    
    bool operator==(ZicanInstrument &zi){
		return (brojZici == zi.brojZici);
    }
    
    friend ostream &operator<<(ostream &stream, ZicanInstrument &zi){
		return stream << zi.ime << " " << zi.brojZici << " " << zi.osnovnaCena << endl;
    }
};

class Mandolina : public ZicanInstrument {
private:
	char forma[20];
public:
	Mandolina(char ime[20] = "", int brojZici = 0, float osnovnaCena = 0, char forma[20] = "")
        : ZicanInstrument(ime, brojZici, osnovnaCena) {
		strcpy(this->forma, forma);
	}

	bool operator==(Mandolina &mandolina){
		return(this->brojZici == mandolina.brojZici);
	}

    friend ostream &operator<<(ostream &stream, Mandolina &mandolina){
		return stream << mandolina.ime << " " << mandolina.brojZici << " " << mandolina.osnovnaCena << endl;
    }
    
	float cena() {
		if (strcmp(forma, "Neapolitan") == 0) {
			return osnovnaCena + (osnovnaCena *0.15);
		}
		else {
			return osnovnaCena;
		}
	}
    
    int getBrojZici() {
    	return brojZici;
    }
};

class Violina : public ZicanInstrument {
private:
	float golemina;
public:
	Violina(char ime[20] = "", int brojZici = 0, float osnovnaCena = 0, float golemina = 0)
        : ZicanInstrument(ime, brojZici, osnovnaCena) {
		this->golemina = golemina;
	}

	bool operator==(const Violina& violina) const {
		return(this->brojZici == violina.brojZici);
	}
    
    friend ostream &operator<<(ostream &stream, Violina &violina){
		return stream << violina.ime << " " << violina.brojZici << " " << violina.osnovnaCena << endl;
    }
    
	float cena() {
		if (golemina == 0.25) {
			return osnovnaCena + (osnovnaCena  * 0.1);
		}
		else if (golemina == 1) {
			return osnovnaCena + (osnovnaCena * 0.2);
		}
		else {
			return osnovnaCena;
		}
	}
    
    int getBrojZici() {
    	return brojZici;
    }
};

void pecatiInstrumenti(ZicanInstrument &zi, ZicanInstrument **i, int n) {
    for(int k = 0; k < n; k++){
        if(zi.getBrojZici() == i[k]->getBrojZici()){
        	cout << i[k]->cena() << endl;
        }
    }
}

int main() {
	char ime[20];
	int brojZici;
	float cena;
	char forma[20];
	cin >> ime >> brojZici >> cena >> forma;
	Mandolina m(ime, brojZici, cena, forma);
	int n;
	cin >> n;
	ZicanInstrument** zi = new ZicanInstrument * [2 * n];
	for (int i = 0; i < n; ++i) {
		cin >> ime >> brojZici >> cena >> forma;
		zi[i] = new Mandolina(ime, brojZici, cena, forma);
	}
	for (int i = 0; i < n; ++i) {
		float golemina;
		cin >> ime >> brojZici >> cena >> golemina;
		zi[n + i] = new Violina(ime, brojZici, cena, golemina);
	}
	pecatiInstrumenti(m, zi, 2 * n);
	for (int i = 0; i < 2 * n; ++i) {
		delete zi[i];
	}
	delete[] zi;
	return 0;
}