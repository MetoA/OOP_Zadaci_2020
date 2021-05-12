/*
Пресек на отсечки Problem 2 (4 / 12) 
Да се напише структура која ќе опишува отсечка во дводимензионален простор (две точки). Потоа да се напише функција која ќе проверува дали две отсечки се сечат.

100%
*/

#include <stdio.h>
#include <string.h>
#include <math.h>

typedef struct Tocka{
  float x;
  float y;
} tocka;

typedef struct Otsecka{
  tocka t1;
  tocka t2;
} otsecka;

int na_linija(otsecka o1, tocka t) {   //dali tockata e na linija
  if((t.x <= fmax(o1.t1.x, o1.t2.x)&&t.x <= fmin(o1.t1.x, o1.t2.x)) && (t.y <= fmax(o1.t1.y, o1.t2.y) && t.y <= fmin(o1.t1.y, o1.t2.y))){
    return 1;
  } else {
    return 0;
  }
}

int nasoka(tocka t1, tocka t2, tocka t3) {
  int val = (t2.y-t1.y)*(t3.x-t2.x)-(t2.x-t1.x)*(t3.y-t2.y);
  if (val == 0){
    return 0; 
  } else if(val < 0){
    return 2;    
    return 1;  // lmao what?
  }  
}

int se_secat(otsecka o1, otsecka o2){
  //four direction for two lines and points of other line
   int dir1 = nasoka(o1.t1, o1.t2, o2.t1);
   int dir2 = nasoka(o1.t1, o1.t2, o2.t2);
   int dir3 = nasoka(o2.t1, o2.t2, o1.t1);
   int dir4 = nasoka(o2.t1, o2.t2, o1.t2);
   
   if(dir1 != dir2 && dir3 != dir4)
      return 1; 

   if(dir1==0 && na_linija(o1, o2.t1)) 
      return 1;

   if(dir2==0 && na_linija(o1, o2.t2)) 
      return 1;

   if(dir3==0 && na_linija(o2, o1.t1)) 
      return 1;

   if(dir4==0 && na_linija(o2, o1.t2)) 
      return 1;
         
   return 0;
}

int main(){
    float x1, y1, x2, y2;
    scanf("%f %f %f %f", &x1, &y1, &x2, &y2);
    tocka t1 = { x1, y1 };
    tocka t2 = { x2, y2 };
    otsecka o1 = { t1, t2 };
    scanf("%f %f %f %f", &x1, &y1, &x2, &y2);
    tocka t3 = { x1, y1 };
    tocka t4 = { x2, y2 };
    otsecka o2 = { t3, t4 };
    printf("%d\n", se_secat(o1, o2));
   
    return 0;
}
