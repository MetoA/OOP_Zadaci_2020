/*
Купувачка кошничка Problem 3 (2 / 34) 
Да се напише програма во која од стандарден влез се вчитува N (бројот на производи), а потоа се вчитуваат податоците за N производи (име, цена, количина). Програмата треба на стандарден излез да ја отпечати листата на купени производи и вкупната сума која треба да се плати во следниот облик (пример):

1. Flips    10.00 x 3 = 30.00
2. CocaCola    75.00 x 2 = 150.00
3. ChokoBanana  5.00 x 10 = 50.00
Total: 230.00

100%
*/

#include <stdio.h>

typedef struct Proizvod{
	char ime[15];
    float cena;
    float kolicina;
} Proizvod;

void printProizvod(int i, Proizvod p){
	printf("%d. %s\t%.2f x %.1f = %.2f\n", i, p.ime, p.cena, p.kolicina, p.cena*p.kolicina);
}

int main(){
	float total = 0;
    int i, N;
    
    scanf("%d", &N);
    Proizvod p[N];
    
    for(i=1; i<=N; i++){
        scanf("%s%f%f", &p[i].ime, &p[i].cena, &p[i].kolicina);
        total += (p[i].cena*p[i].kolicina);
    	printProizvod(i, p[i]);
    }
    printf("Total: %.2f", total);
}