/*
CD Problem 2 (2 / 8)
Да се дефинира класата Pesna во која се чуваат информации за (5 поени):

име на песна (динамички алоцирано поле од знаци)
времетраење на песната во минути
тип на песна кој може да биде: поп, рап или рок (енумерација tip)
Да се обезбедат сите потребни методи за класата за правилно функционирање на програмата. (10 поени)

Дополнително за оваа класа да се дефинира методот:

pecati() - функција во која ќе се печатат одделени со цртичка(-): името на песната во наводници и времетраењето на песната со постфикс min. (5 поени)
Да се креира класата CD во која се чуваат информации за (5 поени):

низа од песни снимени на CD-то (Поле од најмногу 10 објекти од класата Pesna )
број на песни снимени на CD-то
максимално времетраење на песните на CD-то (во минути)
Да се обезбедат сите потребни методи за класата за правилно функционирање на програмата. (5 поени)

Дополнително за оваа класа да се дефинираат методите:

dodadiPesna (Pesna p) - со кој се додава песната p на CDто, но само ако има доволно преостанато место (земајќи го предвид максималното времетраење на песните на CDто и времетраењата на песните на CD-то) и ако има помалку од 10 песни на CD-то. (10 поени)
pecatiPesniPoTip(tip t) – со кој се печатат информациите за сите песни од тип t (поп, рап или рок). (10 поени)
Комплетна функционалност (5 поени).

100%
*/

#include <iostream>
#include <cstring>

using namespace std;
enum tip{pop, rap, rok};
class Pesna{
private:
	char *ime;
    int vreme;
    tip kojtip;
public:
    Pesna(char* ime = "", int vreme = 0, tip kojtip = pop) {
        this->ime = new char[strlen(ime) + 1];
        strcpy(this->ime, ime);

        this->vreme = vreme;
        this->kojtip = kojtip;
    }
    
    Pesna(const Pesna &p){
    	this->ime = new char[strlen(p.ime) + 1];
        strcpy(this->ime, p.ime);

        this->vreme = p.vreme;
        this->kojtip = p.kojtip;
    }
    
    Pesna &operator=(const Pesna &p){
        if(this!=&p){
        	delete[] ime;
            
            this->ime = new char[strlen(p.ime) + 1];
        	strcpy(this->ime, p.ime);

        	this->vreme = p.vreme;
        	this->kojtip = p.kojtip;
        }
        
        return *this;
    }
    
    tip getTip(){
    	return kojtip;
    }
    
    void pecati(){
    	cout<<"\""<<ime<<"\"-"<<vreme<<"min"<<endl;
    }
    
    int getVreme(){
    	return vreme;
    }
    
    ~Pesna(){
    	delete[] ime;
    }
};

class CD{
private:
    Pesna pesni[10];
    int brPesni;
    int maxVreme;
    int currVreme;
public:
    CD(int maxVreme){
    	this->maxVreme = maxVreme;
        brPesni = 0;
        currVreme = 0;
    }
    
    void dodadiPesna(Pesna p){
    	if(currVreme + p.getVreme() >= maxVreme || brPesni >= 10) return;
        
        currVreme += p.getVreme();
        pesni[brPesni] = p;
        incrementBroj();
    }
    
    void pecatiPesniPoTip(tip t){
        for(int i = 0; i <= brPesni; i++){
            if(pesni[i].getTip() == t){
            	pesni[i].pecati();
            }
        }
    }
    
    int getBroj(){
    	return brPesni;
    }
    
    void incrementBroj(){
    	brPesni++;
    }
    
    Pesna getPesna(int i){
    	return pesni[i];
    }
};

int main() {
	// se testira zadacata modularno
    int testCase;
    cin >> testCase;
	
	int n, minuti, kojtip;
	char ime[50];
	
	if(testCase == 1) {
        cout << "===== Testiranje na klasata Pesna ======" << endl;
        cin >> ime;
        cin >> minuti;
        cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
        Pesna p(ime,minuti,(tip)kojtip);
		p.pecati();
    } else if(testCase == 2) {
        cout << "===== Testiranje na klasata CD ======" << endl;
		CD omileno(20);
		cin>>n;
			for (int i=0;i<n;i++){
				cin >> ime;
				cin >> minuti;
				cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
				Pesna p(ime,minuti,(tip)kojtip);
				omileno.dodadiPesna(p);
			}
        	for (int i=0; i<n; i++)
				(omileno.getPesna(i)).pecati();
	}
    else if(testCase == 3) {
        cout << "===== Testiranje na metodot dodadiPesna() od klasata CD ======" << endl;
		CD omileno(20);
		cin>>n;
			for (int i=0;i<n;i++){
				cin >> ime;
				cin >> minuti;
				cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
				Pesna p(ime,minuti,(tip)kojtip);
				omileno.dodadiPesna(p);
			}
        	for (int i=0; i<omileno.getBroj(); i++)
				(omileno.getPesna(i)).pecati();
    }
    else if(testCase == 4) {
        cout << "===== Testiranje na metodot pecatiPesniPoTip() od klasata CD ======" << endl;
		CD omileno(20);
		cin>>n;
			for (int i=0;i<n;i++){
				cin >> ime;
				cin >> minuti;
				cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
				Pesna p(ime,minuti,(tip)kojtip);
				omileno.dodadiPesna(p);
			}
        cin>>kojtip;
        omileno.pecatiPesniPoTip((tip)kojtip);
        	
    }
    else if(testCase == 5) {
        cout << "===== Testiranje na metodot pecatiPesniPoTip() od klasata CD ======" << endl;
		CD omileno(20);
		cin>>n;
			for (int i=0;i<n;i++){
				cin >> ime;
				cin >> minuti;
				cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
				Pesna p(ime,minuti,(tip)kojtip);
				omileno.dodadiPesna(p);
			}
        cin>>kojtip;
        omileno.pecatiPesniPoTip((tip)kojtip);
        	
    }
    
return 0;
}