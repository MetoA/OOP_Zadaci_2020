/*
Филм Problem 3 (4 / 14) 
Да се дефинира класа Film, во која ќе се чуваат информации за:

име низа од 100 знаци
режисер низа од 50 знаци
жанр низа од 50 знаци
година цел број
Сите променливи треба да бидат приватни. Соодветно во рамките на класата да се дефинираат:

default конструктор и конструктор со аргументи
метод за печатење на информациите за филмот
Дополнително да се реализира надворешна функција:

void pecati_po_godina(Film *f, int n, int godina) која ќе прима аргумент низа од филмови, вкупниот број на филмови и година, 
а треба да ги отпечати само филмовите кои се направени во дадената година.

100%
*/

#include <iostream>
#include <cstring>
using namespace std;

// vashiot kod ovde
class Film{
private:
    char ime[100];
    char reziser[50];
    char zanr[50];
    int godina;
public:
    Film(){

    }
    Film(char *ime, char *reziser, char *zanr, int godina){
    	strncpy(this->ime, ime, 100);
        strncpy(this->reziser, reziser, 50);
        strncpy(this->zanr, zanr, 50);
        this->godina = godina;
    }
    
    void setIme(char *ime){
    	strncpy(this->ime, ime, 100);
    }
    
    void setReziser(char *reziser){
    	strncpy(this->reziser, reziser, 50);
    }
    
    void setZanr(char *zanr){
    	strncpy(this->zanr, zanr, 50);
    }
    
    void setGodina(int godina){
    	this->godina = godina;
    }
    
    int getGodina(){
    	return this->godina;
    }
    
    void pecatiFilm(){
    	cout << "Ime: " << ime << endl;
        cout << "Reziser: " << reziser << endl;
        cout << "Zanr: " << zanr << endl;
        cout << "Godina: " << godina << endl;
    }
};

void pecati_po_godina(Film *f, int n, int godina){
    for(int i = 0; i<n; i++){
        if(f[i].getGodina() == godina){
        	f[i].pecatiFilm();
        }
    }
}

int main() {
 	int n;
 	cin >> n;
 	//da se inicijalizira niza od objekti od klasata Film
    Film film[100];
 	for(int i = 0; i < n; ++i) {
 		char ime[100];
 		char reziser[50];
 		char zanr[50];
 		int godina;
 		cin >> ime;
 		cin >> reziser;
 		cin >> zanr;
 		cin >> godina;
 		//da se kreira soodveten objekt
        film[i].setIme(ime);
        film[i].setReziser(reziser);
        film[i].setZanr(zanr);
        film[i].setGodina(godina);
 	}
 	int godina;
 	cin >> godina;
 	//da se povika funkcijata pecati_po_godina
    pecati_po_godina(film, n, godina);
 	return 0;
 }