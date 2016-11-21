#include <stdio.h>

int initialiserTableau( char * buffer , int taille ){

    if( !buffer ) return 0;
    int i;

    for( i = 0 ; i < taille ; i++ ) buffer[i] = '-';

    return 1;
}
