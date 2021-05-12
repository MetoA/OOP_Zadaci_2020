/*
Договор Problem 2 (5 / 17) 
Да се дефинира класа Potpisuvac во која се чуваат информации за:

име (низа од максимум 20 знаци)
презиме (низа од максимум 20 знаци)
ЕМБГ (низа од максимум 14 знаци)
За класата да се дефинира copy конструктор, default конструктор и конструктор со аргументи.

Да се дефинира класа Dogovor, во која се чуваат информации за:

број на договор (int),
категорија на договор (низа од 50 знаци),
поле од 3 потпишувачи на договорот (објекти од класата Potpisuvac)
Во класата да се додаде метод кој ќе проверува дали постојат два исти потпишувачи (имаат ист ЕМБГ).

100%
*/

#include <iostream>
#include <cstring>

using namespace std;

class Potpisuvac
{
	//vasiot kod ovde
private:
    char ime[20];
    char prezime[20];
    char embg[14];
public:
    Potpisuvac(){}
    
    Potpisuvac(char *ime, char *prezime, char *embg){
    	strcpy(this->ime, ime);
        strcpy(this->prezime, prezime);
        strcpy(this->embg, embg);
    }
    
    // copy constructor
    Potpisuvac(const Potpisuvac &potpisuvac){
    	strcpy(this->ime, potpisuvac.ime);
        strcpy(this->prezime, potpisuvac.prezime);
        strcpy(this->embg, potpisuvac.embg);
    }
    
    char *getEMBG(){
    	return embg;
    }
};
class Dogovor
{
    //vasiot kod ovde
private:
	int broj;
	char kategorija[20];
	Potpisuvac potpisuvac[3];
public:
    Dogovor(){}
    
    Dogovor(int broj, char *kategorija, Potpisuvac potpisuvac[]){
    	this->broj = broj;
        strcpy(this->kategorija, kategorija);
        for(int i = 0; i < 3; i++){
        	this->potpisuvac[i] = potpisuvac[i];
        }
    }
    
    bool proverka(){
        for(int i=0; i<3; i++){
            for(int j=i+1; j<3; j++){
                if(strcmp(potpisuvac[i].getEMBG(), potpisuvac[j].getEMBG()) == 0){
                	return true;
                }
            }
        }
        
        return false;
    }    
};


//ne smee da se menuva main funkcijata
int main()
{
    char embg[13], ime[20], prezime[20], kategorija[20];
    int broj, n;
    cin >> n;
    for(int i = 0; i < n; i++){
    	cin >> embg >> ime >> prezime;
    	Potpisuvac p1(ime, prezime, embg);
    	cin >> embg >> ime >> prezime;
    	Potpisuvac p2(ime, prezime, embg);
    	cin >> embg >> ime >> prezime;
    	Potpisuvac p3(ime, prezime, embg);
    	cin >> broj >> kategorija;
    	Potpisuvac p[3];
    	p[0] = p1; p[1] = p2; p[2] = p3;
    	Dogovor d(broj, kategorija, p);
        cout << "Dogovor " << broj << ":" << endl; 
    	if(d.proverka() == true)
    	    cout << "Postojat potpishuvaci so ist EMBG" << endl;
    	else
    	    cout << "Ne postojat potpishuvaci so ist EMBG" << endl;
    }
    return 0;
}