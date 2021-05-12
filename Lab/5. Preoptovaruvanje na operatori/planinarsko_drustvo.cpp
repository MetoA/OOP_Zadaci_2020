/*
Планинарско друштво Problem 3 (1 / 11) 
Да се креира класа за претставување на планинарско друштво во која ќе се чуваат информации за името на друштвото (динамички алоцирана низа од знаци), број на поминати тури (цел број) и број на членови во планинарското друштво (цел број). За оваа класа да се напише:

оператор + за собирање на две друштва што како резултат враќа друштво со број на членови еднаков на збирот од членовите од двете друштва, а останатите атрибути на резултантното друштво ги добиваат вредностите на соодветните атрибути од друштвото со поголем број на членови

оператори >, < за споредба во однос на бројот на членови во планинарските друштва

оператор << за печатење на информациите за планинарското друштво

Да се напише функција што на влез прима низа од планинарски друштва и вкупен број на друштва во низата и го печати планинарското друштво што има најголем број на членови .

100%
*/

#include <iostream>
#include <string.h>
using namespace std;

class PlDrustvo{
private:
    char* ime;
    int brTuri;
    int brClenovi;
public:
    PlDrustvo(char* ime="", int brTuri=0, int brClenovi=0){
        this->ime = new char[strlen(ime)+1];
        strcpy(this->ime, ime);
        this->brTuri = brTuri;
        this->brClenovi = brClenovi;
    }
    
    PlDrustvo(const PlDrustvo& drustvo){
    	this->ime = new char[strlen(drustvo.ime)+1];
        strcpy(this->ime, drustvo.ime);
        this->brTuri = drustvo.brTuri;
        this->brClenovi = drustvo.brClenovi;
    }
    
    ~PlDrustvo(){
    	delete[] ime;
    }
    
    PlDrustvo& operator=(const PlDrustvo& drustvo){
        if(this==&drustvo) return *this;
        if(this!=&drustvo){
        	delete[] ime;
            this->ime = new char[strlen(drustvo.ime)+1];
            strcpy(this->ime, drustvo.ime);
            this->brTuri = drustvo.brTuri;
            this->brClenovi = drustvo.brClenovi;
        }
        
        return *this;
    }
    
    PlDrustvo operator+(const PlDrustvo& drustvo){
        PlDrustvo temp;
        
        temp.brClenovi = this->brClenovi + drustvo.brClenovi;
        
        if(drustvo.brClenovi > this->brClenovi){
            temp.ime = new char[strlen(drustvo.ime)+1];
            strcpy(temp.ime, drustvo.ime);
            temp.brTuri = drustvo.brTuri;
        } else if(drustvo.brClenovi < this->brClenovi){
        	temp.ime = new char[strlen(this->ime)+1];
            strcpy(temp.ime, this->ime);
            temp.brTuri = this->brTuri;
        }
    	
        
        return temp;
    }
    
    friend ostream& operator<<(ostream& stream, const PlDrustvo drustvo){
        return stream<<"Ime: "<<drustvo.ime<<" Turi: "<<drustvo.brTuri<<" Clenovi: "<<drustvo.brClenovi<<endl;	
    }
    
    friend bool operator>(const PlDrustvo& drustvo1, const PlDrustvo& drustvo2); 
    friend bool operator<(const PlDrustvo& drustvo1, const PlDrustvo& drustvo2);
    
    
};

void najmnoguClenovi(PlDrustvo *drustva, int broj){
    	PlDrustvo drustvoNajmnoguClenovi;
        
    	drustvoNajmnoguClenovi = drustva[0];
        for(int i = 1; i < broj; i++){
            if(drustvoNajmnoguClenovi < drustva[i]){
                drustvoNajmnoguClenovi = drustva[i];
            }
        }
        
        cout << "Najmnogu clenovi ima planinarskoto drustvo: " << drustvoNajmnoguClenovi;
    }

bool operator>(const PlDrustvo& drustvo1, const PlDrustvo& drustvo2){
	return (drustvo1.brClenovi > drustvo2.brClenovi);
}

bool operator<(const PlDrustvo& drustvo1, const PlDrustvo& drustvo2){
	return (drustvo1.brClenovi < drustvo2.brClenovi);
}

int main()
{        		
    PlDrustvo drustva[3];
    PlDrustvo pl;
    for (int i=0;i<3;i++)
   	{
    	char ime[100];
    	int brTuri;
    	int brClenovi;
    	cin>>ime;
    	cin>>brTuri;
    	cin>>brClenovi;
    	PlDrustvo p(ime,brTuri,brClenovi);
        drustva[i] = p;
    	
   	}
    
    pl = drustva[0] + drustva[1];
    cout<<pl;
    
    najmnoguClenovi(drustva, 3);
    
    return 0;
}
