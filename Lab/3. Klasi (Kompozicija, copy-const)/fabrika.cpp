/*
Фабрика Problem 3 (2 / 11) 
Креирајте класа Rabotnik која во себе содржи:

ime (низа од максимум 30 знаци)
prezime (низа од максимум 30 знаци)
plata (целобројна вредност)
За оваа класа да се креираат default конструктор и конструктор со аргументи. Да се имплементираат и следните методи:

getPlata() која ја враќа платата на работникот
pecati() која ги печати името, презимето и платата.
Креирајте класа Fabrika во која има:

rabotnik [100] (низа од вработени)
brojVraboteni (целобројна вредност)
Во класата имплементирајте ги следните методи:

pecatiVraboteni() ги печати сите вработени
pecatiSoPlata(int plata) ги печати сите вработени со плата поголема или еднаква на дадената во аргументот (int plata).
Во главната функција се внесуваат податоци за n вработени. Притоа прво се внесува n, па податоците за сите n вработени. Во последниот ред се чита минималната плата.

На излез да се прикажат прво сите вработени, а потоа само оние со поголема плата од минималната. Треба да се корисатат методите pecatiVraboteni и pecatiSoPlata!

100%
*/

#include <iostream>
#include <cstring>

using namespace std;

class Rabotnik{
private:
    char ime[30];
    char prezime[30];
    int plata;
public:
    Rabotnik(){}
    
    Rabotnik(char *ime, char *prezime, int plata){
    	strcpy(this->ime, ime);
        strcpy(this->prezime, prezime);
        this->plata = plata;
    }
    
    void setIme(char *ime){
    	strcpy(this->ime, ime);
    }
    
    void setPrezime(char *prezime){
    	strcpy(this->prezime, prezime);
    }
    
    void setPlata(int plata){
    	this->plata = plata;
    }
    
    int getPlata(){
    	return plata;
    }
    
    void pecati(){
    	cout << ime << " " << prezime << " " << plata << endl;
    }
};

class Fabrika{
private:
    Rabotnik rabotnik[100];
    int brojVraboteni;
public:
    Fabrika(Rabotnik rabotnik[], int brojVraboteni){
        this->brojVraboteni = brojVraboteni;
        for(int i = 0; i < brojVraboteni; i++){
        	this->rabotnik[i] = rabotnik[i];
        }
    }
    
    void pecatiVraboteni(){
        cout << "Site vraboteni:" << endl;
        for(int i=0; i<brojVraboteni; i++){
            
        	rabotnik[i].pecati();
        }
    }
    
    void pecatiSoPlata(int plata){
        cout << "Vraboteni so plata povisoka od " << plata << " :" << endl;
    	for(int i=0; i<brojVraboteni; i++){
            if(rabotnik[i].getPlata() >= plata){
            	rabotnik[i].pecati();
            }
        	
        }
    }
};

int main(){
	char ime[20], prezime[20];
    int plata, n, minPlata;
    
    cin >> n;
    Rabotnik rabotnik[100];
    
    for(int i = 0; i < n; i++){
    	cin >> ime;
        cin >> prezime;
        cin >> plata;
        rabotnik[i].setIme(ime);
        rabotnik[i].setPrezime(prezime);
        rabotnik[i].setPlata(plata);
    }
    
    cin >> minPlata;
    
    Fabrika fab(rabotnik, n);
    
    fab.pecatiVraboteni();
    fab.pecatiSoPlata(minPlata);
}