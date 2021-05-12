/*
Железничка станица Problem 2 (3 / 20)
Да се креира структура Воз во која се чуваат податоци за релацијата по која се движи возот (низа од најмногу 50 знаци), предвиден бројот на километри што треба да се поминат (реален број), како и бројот на патници во возот (цел број).

Потоа да се креирa структура ZeleznickaStanica во која се чуваат податоци за градот во кој се наоѓа (низа од 20 знаци), низа од возови што поаѓаат од станицата (најмногу 30) и бројот на возови (цел број).

Треба да се направи функција со потпис

void najkratkaRelacija(ZeleznickaStanica* zs, int n, char* grad)
во која се печати релацијата и бројот на километри на возот што поминува најкратка релација (најмалку километри), а поаѓа од железничката станица од градот што се проследува како влезен аргумент. Ако има повеќе возови со ист најмал број на километри, да се испечати релацијата на последниот таков.

Забелешка: Задачата да се реши во програмскиот јазик C++

100%
*/

#include<iostream>
#include <cstring>
using namespace std;

struct Voz{
	char relacija[50];
    float predvidenBrKm;
    int brPatnici;
};

struct ZeleznickaStanica{
	char grad[20];
    Voz vozovi[30];
    int brVozovi;
};

int containsGrad(char zsGrad[20], char grad[20]){
    for(int i = 0; i < strlen(grad); i++){
        if(grad[i] != zsGrad[i]) {
            //cout<<strlen(grad)<< endl;
            return false;
        }
    }
    
    return true;
}

void najkratkaRelacija(ZeleznickaStanica* zs, int n, char* grad){
	float minKm;
    char minKmRelacija[50];
    
    for(int i = 0; i < n; i++){
        if(containsGrad(zs[i].vozovi[0].relacija, grad)){
        	minKm = zs[i].vozovi[0].predvidenBrKm;
        }
        
        
        for(int j = 0; j < zs[i].brVozovi; j++){
        	if(containsGrad(zs[i].vozovi[j].relacija, grad)&&zs[i].vozovi[j].predvidenBrKm <= minKm){
        		minKm = zs[i].vozovi[j].predvidenBrKm;
            	strcpy(minKmRelacija, zs[i].vozovi[j].relacija);
        	}
        }
    }
    
    cout<<"Najkratka relacija: "<<minKmRelacija<<" ("<<minKm<<" km)"<<endl;
}

int main(){
	
    int n;
	cin>>n; //se cita brojot na zelezlnichki stanici

    int brojVozovi;
    char gradZS[25];
    float brojKm;
    int brojPatnici;
    char vozRelacija[50];
    
    
    ZeleznickaStanica zStanica[100];
    for (int i=0;i<n;i++){
        cin>>gradZS;
        strcpy(zStanica[i].grad, gradZS);
        
        cin>>brojVozovi;
        zStanica[i].brVozovi = brojVozovi;
        for(int j = 0; j < brojVozovi; j++){
        	cin>>vozRelacija>>brojKm>>brojPatnici;
            strcpy(zStanica[i].vozovi[j].relacija, vozRelacija);
            zStanica[i].vozovi[j].predvidenBrKm = brojKm;
            zStanica[i].vozovi[j].brPatnici = brojPatnici;
        }
        //se citaat infomracii za n zelezlnichkite stanici i se zacuvuvaat vo poleto zStanica
    }
    
    char grad[25];
    cin>>grad;

	najkratkaRelacija(zStanica,n,grad);
	return 0;
}
