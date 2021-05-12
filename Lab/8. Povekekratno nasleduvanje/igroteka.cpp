/*
Игротека Problem 2 (2 / 4) 
Во една игротека има 2 типа играчки: топки и коцки. Коцките и топките се опишани со параметри како што се:

боја (char *)
густина (int).
Дополнително за топките се знае и радиусот (int), додека за коцките целосните димензии (висина, ширина и длабочина – int).

За секоја од класите треба да се дефинираат методи getMasa() и getVolumen(). Масата на играчката се пресметува како производ од волуменот и густината на играчката. За PI користете ја вредноста 3.14.

Во функцијата main да се декларира променлива kupche што претставува динамички алоцирана низа кон Igrachka. Во зависност од првиот влезен параметар се внесуваат објекти од класите Topka или Kocka (1 - се внесува топка, 2 - се внесува коцка).

Од тастатура да се внесат податоци за коцката на Петра Kocka petra. Во главната функција во да се отпечатат:

Да се отпечати DA ако вкупната маса на сите играчки е поголема од масата на играчката на Петра, а NE во спротивно.
Разликата по апсолутна вредност на волуменот на играчката со максимален волумен во купчето и волуменот на коцката на Петра. Форматот е:

Razlikata e: {razlika}

Задачата да се реши со тоа што класите Kocka и Topka ќе наследуваат од класите Forma и Igrachka.

Дополнителни барања:

Во класата Igrachka да се додаде уште една чисто виртуелна функција float getPlostina(). Истата да се имплементира во класите Kocka и Topka
Во главната функција, дополнително да се испечати и: Разликата по апсолутна вредност на плоштината на играчката со минимална плоштина во купчето и плоштината на коцката на Петра во истиот формат како и второто барање погоре.

100%
*/

#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;

class Igrachka {
public:
    virtual float getVolumen() = 0;
    virtual float getMasa() = 0;
    
    //дополнително барање 1
    virtual float getPlostina() = 0;
};

class Forma {
protected:
    char boja[100];
    int gustina;
public:
    // да се имплементираат потребните методи
    
    Forma(char *boja = "", int gustina = 0){
    	strcpy(this->boja, boja);
        this->gustina = gustina;
    }
};

class Kocka : public Forma, public Igrachka{
private:
	int visina;
    int shirina;
    int dlabocina;
public:
    Kocka(char *boja = "", int gustina = 0, int visina = 0, int shirina = 0, int dlabocina = 0)
    : Forma(boja, gustina){
    	this->visina = visina;
        this->shirina = shirina;
        this->dlabocina = dlabocina;
    }
    
    float getVolumen(){
    	return this->visina * this->shirina * this->dlabocina;
    }
    
    float getMasa(){
    	return this->getVolumen() * this->gustina;
    }
    
    float getPlostina(){
    	return 2*(this->visina * this->shirina + this->shirina * this->dlabocina + this->visina * this->dlabocina);
    }
    
};

class Topka : public Forma, public Igrachka{
private:
    int radius;
public:
    Topka(char *boja = "", int gustina = 0, int radius = 0)
    : Forma(boja, gustina){
    	this->radius = radius;
    }
    
    float getVolumen(){
    	return (4.0/3) * 3.14 * radius * radius * radius;
    }
    
    float getMasa(){
    	return this->getVolumen() * this->gustina;
    }
    
    float getPlostina(){
    	return 4 * 3.14 * radius * radius;
    }
    
};




int main(){
	//vnesi informacii za kupche
    
    int n, tip, gustina, visina, shirina, dlabocina, radius;
    char boja[15];
    
    cin >> n;
    
	Igrachka **kupche = new Igrachka*[n];
    
    for(int i = 0; i < n; i++){
        cin >> tip >> boja >> gustina;
        if(tip == 1){
        	cin >> radius;
            kupche[i] = new Topka(boja, gustina, radius);
        } else if(tip == 2){
        	cin >> visina >> shirina >> dlabocina;
            kupche[i] = new Kocka(boja, gustina, visina, shirina, dlabocina);
        }
    }
    //vnesi informacii za igrachkata na Petra
    
    cin >> boja >> gustina >> visina >> shirina >> dlabocina;
    Kocka petra(boja, gustina, visina, shirina, dlabocina);
    
	//baranje 1
    
    float vkupnaMasa = 0;
    float maxVolumen = kupche[0]->getVolumen();
    float minPlostina = kupche[0]->getPlostina();
    
    for(int i = 0; i < n; i++){
    	vkupnaMasa += kupche[i]->getMasa();
        
        if(kupche[i]->getVolumen() > maxVolumen){
        	maxVolumen = kupche[i]->getVolumen();
        }
        
        if(kupche[i]->getPlostina() < minPlostina){
        	minPlostina = kupche[i]->getPlostina();
        }
    }
    
    if(vkupnaMasa > petra.getMasa()){
    	cout << "DA" << endl;
    } else {
    	cout << "NE" << endl;
    }


	//baranje 2
    
    cout << "Razlikata e: " << abs(maxVolumen - petra.getVolumen()) << endl;
    
    //дополнително барање 2
    
    cout << "Razlikata e: " << abs(minPlostina - petra.getPlostina()) << endl;

	return 0;
}