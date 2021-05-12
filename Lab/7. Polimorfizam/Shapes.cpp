/*
Shapes Problem 7 (1 / 2) 
--

Потребно е да конструирате абстракна класа Shape со само еден параметар:

страна (int)
Конструктори:

Shape()
Shape(int a)
И виртуелните методи:

double plostina()
void pecati()
int getType()
Од таа класа вие треба да конструирате 3 изведени класи:

Square
Circle
Triangle
Изведените класи немаат дополнителни парамтери, туку ја наследуваат страната од Shape

Конструктори:

Конструкторот на изведените класи ќе зема еден аругмент, страната на фигурата.

При пишување на конструкторот на изведените класи да се искористи констукторот на родител класата

Методи:

Секоја од класите си има своја формула за plostina() соодветна за нивната геометриска фигура

Формула за плоштина на квадрат а * a
Формула за плоштина на круг 3.14 * a * a
Формула за плоштина на триаголник (sqrt(3)/4) * side * side
За pecati() методот упатете се кон outputot за тест случајите.

getType() методот треба да враќа:

1 за Square
2 за Circle
3 за Triangle
Поени: 5

--

Дефинирајте го методот void checkNumTypes(Shape** niza, int n) така што ќе испечати во три реда колку квадрати, кругови и триаголници има во низата.

Поени: 2

--

Покрај тоа треба да ја допишете Main класата така што ќе алоцирате динамичка низа од покажувачи кон класата Shape.

Потоа кај секој покажувач од низата зависно од дадениот input да алоцирате објект од една од трите изведени класи.

Input:

Прво се добива n - големината на динамичката низа. Потоа n пати се добиваат пар цели броеви t i a, каде што t е типот на објектот и а е страната на објектот.

Пример:

3

1 3 //квадрат со страна со должина 3

2 2 //круг со страна со должина 2

3 1 //триаголник со страна со должина 1

Поени: 3

--

100%
*/

#include <iostream>
#include <cmath>
using namespace std;


//TODO: konstruiraj ja abstraknata klasa Shape
class Shape{
protected:
    int strana;
public:
    Shape(){
    
    }
    
    Shape(int a){
    	strana = a;
    }
    
    virtual double plostina() const = 0;
    virtual void pecati() const = 0;
    virtual int getType() const = 0;
};
//TODO: konstruiraj ja klasata Kvadrat
class Square : public Shape{
public:
    Square(int a) : Shape(a){
    }
    
    double plostina() const{
    	return (double)strana*strana;
    }
    
    void pecati() const{
    	cout << "Kvadrat so plostina = " << plostina() << endl;
    }
    
    int getType() const{
    	return 1;
    }
};
//TODO: konstruiraj ja klasata Krug
class Circle : public Shape{
public:
    Circle(int a) : Shape(a){
    }
    
    double plostina() const{
    	return 3.14*strana*strana;
    }
    
    void pecati() const{
    	cout << "Krug so plostina = " << plostina() << endl;
    }
    
    int getType() const{
    	return 2;
    }
};
//TODO: konstruiraj ja klasata Triagolnik
class Triangle : public Shape{
public:
    Triangle(int a) : Shape(a){
    }
    
    double plostina() const{
    	return (sqrt(3)/4) * strana * strana;
    }
    
    void pecati() const{
    	cout << "Triagolnik so plostina = " << plostina() << endl;
    }
    
    int getType() const{
    	return 3;
    }
};

//TODO: definiraj go metodot void checkNumTypes(Shape** niza, int n)
void checkNumTypes(Shape** niza, int n){
	int numSquare = 0, numCircle = 0, numTriangle = 0;
    
    for(int i = 0; i < n; i++){
        if(niza[i]->getType() == 1){
        	numSquare++;
        } else if(niza[i]->getType() == 2){
        	numCircle++;
        } else if(niza[i]->getType() == 3){
        	numTriangle++;
        }
    }
    
    cout << "Broj na kvadrati vo nizata = " << numSquare << endl;
    cout << "Broj na krugovi vo nizata = " << numCircle << endl;
    cout << "Broj na triagolnici vo nizata = " << numTriangle << endl;
}

int main(){


	int n;
	cin >> n;

	//TODO: inicijaliziraj niza od pokazuvachi kon klasata Shape
	Shape** niza;
	

	//TODO: alociraj memorija so golemina n za prethodno navedenata niza
	niza = new Shape*[n];

	int classType;
	int side;

	//TODO: konstruiraj for ciklus so chija pomosh ke ja popolnish nizata
	for(int i = 0; i < n; ++i){

		cin >> classType;
		cin >> side;
		
        if(classType == 1){
        	niza[i] = new Square(side);
        } else if(classType == 2){
        	niza[i] = new Circle(side);
        } else if(classType == 3){
        	niza[i] = new Triangle(side);
        }
	}
    
    
	for(int i = 0; i < n; ++i){

		niza[i]->pecati();
	}

	checkNumTypes(niza, n);


    delete[] niza;
	return 0;
}