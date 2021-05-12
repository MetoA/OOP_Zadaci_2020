/*
Трансакции (simple version) Problem 4 (2 / 8) 
Да се креира класа Transakcija во која што ќе се чуваат информации за:

датумот на реализирање на банкарската трансакција:
ден (int)
месец (int)
година (int)
паричниот износ кој се однесува на трансакцијата (позитивен или негативен, тип double)
моменталната вредност на еврото во денари (static double EUR), иницијално поставен на 61
моменталната вредност на доларот во денари (static double USD), иницијално поставен на 50
За класата да се имплемтнираат соодветните конструктори, како и да се дефинираат следните четири чисто виртуелни методи:

double voDenari()
void pecati()
Трансакциите можат да бидат денарски и девизни (DenarskaTransakcija и DeviznaTransakcija). За девизните трансакции се чува дополнителна информација за валутата на трансакцијата (низа од три знаци). Дозволени валути за девизните транскации се USD и EUR.

За двете изведени класи да се напишат соодветните конструктори, деструктори и да се препокријат потребните методи.

Да се дефинира класа Smetka во која што ќе се чуваат информации за:

извршените трансакции (динамички алоцирана низа од покажувачи кон класата Transakcija)
број на извршените трансакции (int)
број на сметката (низа од 15 знаци)
почетно салдо во денари (double)
За класата Smetka да се имплементираат:

потребен конструктор (со два аргументи, видете во main), деструктор
оператор за додавање на нова трансакција во низата од трансакции +=
void izvestajVoDenari() - функција што печати информации за сметката во форматот:

Korisnikot so smetka: [број на сметката] ima momentalno saldo od [салдо на сметката пресметано во денари] MKD

void pecatiTransakcii() - функција што ги печати сите внесени трансакции

Да се креираат класи за следните исклучоци:

InvalidDateException којшто се фрла доколку при креирање на трансакција не се испочитувани правилата 1<=ден<=31 и 1<=месец<=12
NotSupportedCurrencyException којшто се фрла доколку при креирање на девизна трансакција се внесува вредност за валута што не е дозволена
Овие исклучоци да се фрлат и да се фатат таму каде што е потребно. Истите при фаќање треба да печатат пораки од следниот формат:

Invalid Date 32/12/2018
GBP is not a supported currency

100%
*/

#include<iostream>
#include<cstring>

using namespace std;

class InvalidDateException{
private:
    int den;
    int mesec;
    int godina;
public:
    InvalidDateException(int den, int mesec, int godina){
    	this->den = den;
        this->mesec = mesec;
        this->godina = godina;
    }
    
    void message(){
    	cout<<"Invalid Date "<<den<<"/"<<mesec<<"/"<<godina<<endl;
    }
};

class NotSupportedCurrencyException{
private:
    char valuta[3];
public:
    NotSupportedCurrencyException(char* valuta){
    	strcpy(this->valuta, valuta);
    }
    
    void message(){
    	cout<<valuta<<" is not a supported currency"<<endl;
    }
};

class Transakcija{
protected:
    int den;
    int mesec;
    int godina;
    double paricenIznos;
    static double EUR;
    static double USD;
public:
    Transakcija(int den = 1, int mesec = 1, int godina = 1, double paricenIznos = 0){
        if(den<1 || den>31 || mesec<1 || mesec>12){
        	throw InvalidDateException(den, mesec, godina);
        }
        
    	this->den = den;
        this->mesec = mesec;
        this->godina = godina;
        this->paricenIznos = paricenIznos;
    }
    
    Transakcija(const Transakcija &t){
    	this->den = t.den;
        this->mesec = t.mesec;
        this->godina = t.godina;
        this->paricenIznos = t.paricenIznos;
    }
    
    virtual double voDenari() = 0;
	virtual void pecati() = 0;
    
    static void setUSD(double usd){
    	Transakcija::USD = usd;
    }
    
    static void setEUR(double eur){
    	Transakcija::EUR = eur;
    }
    
    static double getEUR(){
    	return Transakcija::EUR;
    }
    
    static double getUSD(){
    	return Transakcija::USD;
    }
};

double Transakcija::EUR = 61;
double Transakcija::USD = 50;

class DenarskaTransakcija : public Transakcija{
public:
    DenarskaTransakcija(int den, int mesec, int godina, double paricenIznos)
        :Transakcija(den, mesec, godina, paricenIznos){
        
        }
    
    double voDenari(){
    	return this->paricenIznos;
    }
    
    void pecati(){
    	cout<<den<<"/"<<mesec<<"/"<<godina<<" "<<paricenIznos<<" MKD"<<endl;
    }
};

class DeviznaTransakcija : public Transakcija{
private:
    char valuta[4];
public:
    DeviznaTransakcija(int den, int mesec, int godina, double paricenIznos, char* valuta)
        :Transakcija(den, mesec, godina, paricenIznos){
            if(strcmp(valuta, "EUR") == 0 || strcmp(valuta, "USD") == 0){
            	strcpy(this->valuta, valuta);
            } else {
            	throw NotSupportedCurrencyException(valuta);
            }
        }
    
    double voDenari(){
        if(strcmp(valuta, "EUR") == 0){
        	return this->paricenIznos*EUR;
        }
    	return this->paricenIznos*USD;
        //return this->paricenIznos;
    }
    
    void pecati(){
    	if(strcmp(valuta, "EUR") == 0){
        	cout<<den<<"/"<<mesec<<"/"<<godina<<" "<<paricenIznos<<" EUR"<<endl;
        } else {
        	cout<<den<<"/"<<mesec<<"/"<<godina<<" "<<paricenIznos<<" USD"<<endl;
        }
        
    	
    	
    }
};

class Smetka{
private:
    Transakcija** transakcii;
	int izvrseniTransakcii;
    char brojSmetka[15];
    double saldo;
public:
    Smetka(char* brojSmetka = "", double saldo = 0){
    	strcpy(this->brojSmetka, brojSmetka);
        this->saldo = saldo;
        transakcii = new Transakcija*[0];
        izvrseniTransakcii = 0;
    }
    
    ~Smetka(){
    	delete[] transakcii;
    }
    
    Smetka &operator+=(Transakcija *t){
    	Transakcija **temp = new Transakcija*[izvrseniTransakcii+1];
        
        for(int i = 0; i < izvrseniTransakcii; i++){
        	temp[i] = transakcii[i];
        }
        
        temp[izvrseniTransakcii++] = t;
        delete[] transakcii;
        transakcii = temp;
        
        return *this;
    }
    
    void izvestajVoDenari(){
        double sum = this->saldo;
        for(int i = 0; i < izvrseniTransakcii; i++){
        	sum+=transakcii[i]->voDenari();
        }
    	cout<<"Korisnikot so smetka: "<<brojSmetka<<" ima momentalno saldo od "<<sum<<" MKD"<<endl;
    }	
    
    void pecatiTransakcii(){
        for(int i = 0; i < izvrseniTransakcii; i++){
        	transakcii[i]->pecati();
        }
    }
};

int main () {
	
	Smetka s ("300047024112789",1500);
	
	int n, den, mesec, godina, tip;
	double iznos;
	char valuta [3];
	
	cin>>n;
    cout<<"===VNESUVANJE NA TRANSAKCIITE I SPRAVUVANJE SO ISKLUCOCI==="<<endl;
	for (int i=0;i<n;i++){
        cin>>tip>>den>>mesec>>godina>>iznos;
		 try{
			if (tip==2){
				cin>>valuta;
				Transakcija * t = new DeviznaTransakcija(den,mesec,godina,iznos,valuta);
				s+=t;
            	//delete t;
			}
			else {
				Transakcija * t = new DenarskaTransakcija(den,mesec,godina,iznos);
				s+=t;
            	//delete t;
			}
        }
        catch(InvalidDateException &err){
        	err.message();
        }
        catch(NotSupportedCurrencyException &err){
        	err.message();
        }
			
	}
    cout<<"===PECHATENJE NA SITE TRANSAKCII==="<<endl;
    s.pecatiTransakcii();
    cout<<"===IZVESHTAJ ZA SOSTOJBATA NA SMETKATA VO DENARI==="<<endl;
    s.izvestajVoDenari();
   
    
    cout<<"\n===PROMENA NA KURSOT NA EVROTO I DOLAROT===\n"<<endl;
    
        
    double newEUR, newUSD;
    cin>>newEUR>>newUSD;
    Transakcija::setEUR(newEUR);
    Transakcija::setUSD(newUSD);
    cout<<"===IZVESHTAJ ZA SOSTOJBATA NA SMETKATA VO DENARI==="<<endl;
    s.izvestajVoDenari();
    
    
	
	
	return 0;
}