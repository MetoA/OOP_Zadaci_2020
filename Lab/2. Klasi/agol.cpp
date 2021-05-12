/*
Агол Problem 1 (2 / 5) 
Да се дефинира класа Agol, во која се чуваат информации за:

степени, минути и секунди (int)
Во класата да се реализираат:

конструктор по потреба
методи за поставување на вредности на атрибутите на класата (set методи)
метод за пресметување на вредноста на аголот во секунди
Да се дефинира и метод за проверување на тоа дали внесениот агол е валиден, односно дали се внесени соодветни вредности за атрибутите (во границите кои ги дозволуваат).

100%
*/

#include <iostream>
using namespace std;

class Agol {
private:
    int deg;
    int min;
    int sec;
public:
    void set_stepeni(int deg) {
		this->deg = deg;
    }
    void set_minuti(int min) {
		this->min = min;
    }
    void set_sekundi(int sec) {
		this->sec = sec;
    }
    int getSekundi() {
        return sec;
    }
    
    int to_sekundi() {
		return (this->deg * 60 * 60) + (this->min * 60) + this->sec;
    }
};  

int proveri(int deg, int min, int sec) {
        if (deg >= 0&&deg <= 360) {
            if (min >= 0&&min < 60) {
                if (sec >= 0 && sec < 60) {
                    return 1;
                }
                else {
                    return 0;
                }
            }
            else {
                return 0;
            }
        }
        else {
            return 0;
        }
    }

bool changeOfSeconds(Agol a, int sec) {
    return a.getSekundi() != sec;
}

int main() {

    //da se instancira objekt od klasata Agol
    Agol a1;
    int deg, min, sec;
    cin >> deg >> min >> sec;

    if (proveri(deg, min, sec)) {

        a1.set_stepeni(deg);
        a1.set_minuti(min);
        a1.set_sekundi(sec);
        cout << a1.to_sekundi();
        if (changeOfSeconds(a1, sec))
            cout << "Ne smeete da gi menuvate sekundite vo ramkite na klasata!" << endl;

    } else {
    	cout << "Nevalidni vrednosti za agol" << endl;
    }

    return 0;
}