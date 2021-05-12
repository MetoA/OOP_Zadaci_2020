/*
Недвижнина Problem 1 (2 / 3) 
Да се развие класа Nediviznina за коjа се чуваат следниве информации:

адреса (динамички алоцирана низа од знаци)
квадратура (цел боj)
цена за квадрат (цел боj)
За оваа класа да се имплементираат соодветните конструктори и следните методи:

cena() коj ќе jа враќа цената на недвижнината (квадратура * цена-за-квадрат)
pecati() коj ќе ги испечати сите информации за истата
danokNaImot() коj го ваќа данокот што се плаќа за недвижнината, а истиот се пресметува како 5% од цената на недвижнината.
Од оваа класа да се изведе класа Vila за коjа дополнително се чува данок на луксуз (цел боj, пр. 10%). За оваа класа да се преоптоварат методите:

pecati()
danokNaImot() со тоа што пресметаниот данок се зголемува процентуално за данокот на луксуз.
И за двете класи треба да се преоптовари operator >>.

100%
*/

//Vasiot kod ovde....
#include <iostream>
#include <cstring>

using namespace std;

class Nedviznina{
protected:
    char *adresa;
    int kvadratura;
    int cenaKvadrat;
public:
    Nedviznina(const char *adresa = "", int kvadratura = 0, int cenaKvadrat = 0){
    	this->adresa = new char[strlen(adresa)+1];
        strcpy(this->adresa, adresa);
        this->kvadratura = kvadratura;
        this->cenaKvadrat = cenaKvadrat;
    }
    
    ~Nedviznina(){
    	delete[] adresa;
    }
    
    char *getAdresa(){
    	return adresa;
    }
    
    int cena(){
    	return kvadratura * cenaKvadrat;
    }
    
    void pecati(){
    	cout << adresa << ", Kvadratura: " << kvadratura << ", Cena po Kvadrat: " << cenaKvadrat << endl;
    }
    
    float danokNaImot(){
    	return cena()/100.0*5.0;
    }
    
    friend istream &operator>> (istream &stream, Nedviznina &nedviznina){
    	return stream >> nedviznina.adresa >> nedviznina.kvadratura >> nedviznina.cenaKvadrat;
    }
};

class Vila : public Nedviznina{
private:
    int danok;
public:
    void pecati(){
    	cout << adresa << ", Kvadratura: " << kvadratura << ", Cena po Kvadrat: " << cenaKvadrat << ", Danok na luksuz: " << danok << endl;
    }
    
    float danokNaImot(){
    	return Nedviznina::danokNaImot() * (danok/5+1);
    }
    
    friend istream &operator>> (istream &stream, Vila &vila){
    	return stream >> vila.adresa >> vila.kvadratura >> vila.cenaKvadrat >> vila.danok;
    }
};

int main(){
    Nedviznina n;
    Vila v;
    cin>>n;
    cin>>v;
    n.pecati();
    cout<<"Danok za: "<<n.getAdresa()<<", e: "<<n.danokNaImot()<<endl;
    v.pecati();
    cout<<"Danok za: "<<v.getAdresa()<<", e: "<<v.danokNaImot()<<endl;
    return 0;
}