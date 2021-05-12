/*
Задача 2 Problem 2 (2 / 2) 
Да се дефинира класата Film во која се чуваат информации за:

име на филмот (динамички алоцирано поле од знаци)
мемориската зафатнина на филмот изразена во MB
жанр на филмот кој може да биде: акција, комедија или драма (енумерација zanr)
Да се обезбедат сите потребни методи за класата за правилно функционирање на програмата.

Дополнително за оваа класа да се дефинира функцијата:

pecati() - функција во која ќе се печатат одделени со цртичка(-): мемориска зафатнина на филмот со постфикс MB и името на филмот во наводници.
Да се креира класата DVD во која се чуваат информации за :

низа од филмови снимени на DVD-то (Поле од најмногу 5 објекти од класата Film )
број на филмови снимени на DVD-то
меморискиот капацитет на DVD-то (во MB)
Да се обезбедат сите потребни методи за класата за правилно функционирање на програмата.

Дополнително за оваа класа да се дефинираат методите:

dodadiFilm (Film f) - со кој се додава филмот f на DVDто, но само ако има доволно преостанато место (земајќи го предвид меморискиот капацитет на DVD-то и мемориската зафатнина на снимените филмови) и притоа да има помалку од 5 филмови на DVD-то.
pecatiFilmoviDrugZanr(zanr z) – со кој се печатат информациите за сите филмови кои НЕ се од жанрот zanr (акција, комедија или драма).
(дополнително барање):float procentNaMemorijaOdZanr(zanr z)- со кој се пресметува процентот на меморијата која ја зафаќаат филмовите од жанр z на DVD-то.

100%
*/

#include <iostream>
#include <cstring>

using namespace std;

enum zanr {akcija, komedija, drama};

class Film{
private:
    char *ime;
    int memorija;
    zanr genre;
public:
    Film(const char *ime = "", int memorija = 0, zanr genre = zanr(0)){
    	this->ime = new char[strlen(ime) +1];
        strcpy(this->ime, ime);
        this->memorija = memorija;
        this->genre = genre;
    }
    
    Film &operator = (const Film &film){
        if(this!=&film){
        	delete[] this->ime;
            this->ime = new char[strlen(film.ime) +1];
        	strcpy(this->ime, film.ime);
        	this->memorija = film.memorija;
        	this->genre = film.genre;
        }
        return *this;
    }
    
    int getMemorija(){
    	return this->memorija;
    }
    
    zanr getZanr(){
    	return genre;
    }
    
    void pecati(){
    	cout << this->memorija << "MB-\"" << this->ime << "\"" << endl;
    }
};

class DVD{
private:
    Film filmovi[5];
    int brFilmovi;
    int kapacitet;
public:
    DVD(int kapacitet = 0, Film *filmovi = NULL, int brFilmovi = 0){
    	this->kapacitet = kapacitet;
        this->brFilmovi = brFilmovi;
        for(int i = 0; i < brFilmovi; i++){
        	this->filmovi[i] = filmovi[i];
        }
    }
    
    void dodadiFilm(Film &f){
    	int zbir = 0;
        for(int i = 0; i < brFilmovi; i++){
        	zbir += filmovi[i].getMemorija();
        }
        if(kapacitet - zbir >= f.getMemorija()&&brFilmovi < 5){
        	filmovi[brFilmovi++] = f;
        }
    }
    
    void pecatiFilmoviDrugZanr(zanr z){
        for(int i = 0; i < brFilmovi; i++){
            if(filmovi[i].getZanr() != z){
            	filmovi[i].pecati();
            }
        }
    }
    
    float procentNaMemorijaOdZanr(zanr z){
    	float memorijaOdZanr = 0;
        float vkMemorija;
        for(int i = 0; i < brFilmovi; i++){
            if(filmovi[i].getZanr() == z){
            	memorijaOdZanr += filmovi[i].getMemorija();
            }
            vkMemorija += filmovi[i].getMemorija();
        }
        return memorijaOdZanr/vkMemorija*100;
    }
    
    Film &getFilm(int i){
    	return filmovi[i];
    }
    
    int getBroj(){
    	return brFilmovi;
    }
};

int main() {
    // se testira zadacata modularno
    int testCase;
    cin >> testCase;

    int n, memorija, kojzanr;
    char ime[50];

    if (testCase == 1) {
        cout << "===== Testiranje na klasata Film ======" << endl;
        cin >> ime;
        cin >> memorija;
        cin >> kojzanr; //se vnesuva 0 za AKCIJA,1 za KOMEDIJA i 2 za DRAMA
        Film f(ime, memorija, (zanr) kojzanr);
        f.pecati();
    } else if (testCase == 2) {
        cout << "===== Testiranje na klasata DVD ======" << endl;
        DVD omileno(50);
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> memorija;
            cin >> kojzanr; //se vnesuva 0 za AKCIJA,1 za KOMEDIJA i 2 za DRAMA
            Film f(ime, memorija, (zanr) kojzanr);
            omileno.dodadiFilm(f);
        }
        for (int i = 0; i < n; i++)
            (omileno.getFilm(i)).pecati();
    } else if (testCase == 3) {
        cout << "===== Testiranje na metodot dodadiFilm() od klasata DVD ======" << endl;
        DVD omileno(50);
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> memorija;
            cin >> kojzanr; //se vnesuva 0 za AKCIJA,1 za KOMEDIJA i 2 za DRAMA
            Film f(ime, memorija, (zanr) kojzanr);
            omileno.dodadiFilm(f);
        }
        for (int i = 0; i < omileno.getBroj(); i++)
            (omileno.getFilm(i)).pecati();
    } else if (testCase == 4) {
        cout << "===== Testiranje na metodot pecatiFilmoviDrugZanr() od klasata DVD ======" << endl;
        DVD omileno(50);
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> memorija;
            cin >> kojzanr; //se vnesuva 0 za AKCIJA,1 za KOMEDIJA i 2 za DRAMA
            Film f(ime, memorija, (zanr) kojzanr);
            omileno.dodadiFilm(f);
        }
        cin >> kojzanr;
        omileno.pecatiFilmoviDrugZanr((zanr) kojzanr);

    } else if (testCase == 5) {
        cout << "===== Testiranje na metodot pecatiFilmoviDrugZanr() od klasata DVD ======" << endl;
        DVD omileno(50);
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> memorija;
            cin >> kojzanr; //se vnesuva 0 za AKCIJA,1 za KOMEDIJA i 2 za DRAMA
            Film f(ime, memorija, (zanr) kojzanr);
            omileno.dodadiFilm(f);
        }
        cin >> kojzanr;
        omileno.pecatiFilmoviDrugZanr((zanr) kojzanr);

    } else if (testCase == 6){
		cout<<"===== Testiranje na metodot procentNaMemorijaOdZanr() od klasata DVD =====" <<endl;
		DVD omileno(40);
		cin >> n;
		for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> memorija;
            cin >> kojzanr; //se vnesuva 0 za AKCIJA,1 za KOMEDIJA i 2 za DRAMA
            Film f(ime, memorija, (zanr) kojzanr);
            omileno.dodadiFilm(f);
        }
        cin >> kojzanr;
        cout<<"Procent na filmovi od dadeniot zanr iznesuva: "<<omileno.procentNaMemorijaOdZanr((zanr) kojzanr)<<"%\n";
		
	}

    return 0;
}