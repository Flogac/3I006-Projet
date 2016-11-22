#include <stdio.h>
#include <stdlib.h>
#include "algo_reponse.h"

Liste * mainSOL2( char * X , char * Y , int tailleX , int tailleY , int dxy , int dgap ){
  int i;

  char X2ae[3];
  char Y2ae[tailleX + 1];
char * F2ae[3];
for ( i = 0 ; i < 3 ; i++ ) F2ae[i] = (char * ) malloc( sizeof( int ) * (tailleX + 1));
char X2be[tailleY + 1];
char Y2be[3] ;
char * F2be[tailleY+1];
for ( i = 0 ; i <= tailleY ; i++ ) F2be[i] = (char * ) malloc( sizeof( int ) * (3));
Liste * L;
appelSOL2( X2ae , Y2ae , F2ae , X2be , Y2be , F2be , 0 ,  0 , tailleX - 1 , tailleY - 1 , &L , X , Y , dxy , dgap , tailleX , tailleY );

trie( L );

return L;
}

int main(){

char * nomfichier = "toto";
char * X;
char * Y;
int tailleX;
int tailleY;
int dxy = 3;
int dgap = 2;

lectureTableau( nomfichier , &X , &Y , &tailleX , &tailleY );
afficherListe( SOL1( X , tailleX , Y , tailleY , dxy , dgap) );
printf( "SOL1 fini, début SOL2.\n");
afficherListe( mainSOL2( X , Y , tailleX , tailleY , dxy , dgap ));
printf( "SOL2 fini\n");

return 0;
}
