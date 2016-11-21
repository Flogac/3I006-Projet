#include <stdio.h>

int initialiserTableau( char * buffer , int taille ){

    if( !buffer ) return 0;
    int i;

    for( i = 0 ; i < taille ; i++ ) buffer[i] = '-';

    return 1;
}

int min3( int a , int b , int c ){
    if( a < b ) if( a < c ) return a;
    if( b < c ) return b;
    return c;
}
