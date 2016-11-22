#include <stdio.h>
#include <stdlib.h>
#include "listes.h"

Liste * nouvelleListe( char a , char b , Liste * precedent , Liste * suivant , int indicea , int indiceb ){
    Liste * retour = ( Liste * ) malloc ( sizeof( Liste ) );
    retour->x = a;
    retour->y = b;
    retour->precedent = precedent;
    retour->suivant = suivant;
    retour->poids = 0;
    retour->indicex = indicea;
    retour->indicey = indiceb;
    return retour;
}

Liste * dernier( Liste * a ){
    if( !a ) return NULL;
    return a->precedent;
}

void concatener( Liste ** a , Liste * b ){
    if( !a ) return;
    if( !b ) return;
    if( !*a ) {
            *a = b;
            return;
    }
    Liste * c = dernier( *a );
    if( !c ) return;
    c->suivant = b;
    (*a)->precedent = dernier(b);
    b->precedent = c;
}

void coupe( Liste *  a){
    if(!a) return;
    Liste * b = a->precedent->precedent;
    free( a->precedent );
    a->precedent = b;
}

void trie( Liste * a ){
    if(!a ) return;
    int i ;
    Liste * temp;
    Liste * temp2;

    do{
        i = 0;
        temp = a;
        while( temp->suivant ){
            if( temp->x != '-' && temp->indicex > temp->suivant->indicex ){
                temp2 = temp->suivant->suivant;
                if(temp->precedent->suivant) temp->precedent->suivant = temp->suivant;
                temp->precedent->suivant->precedent->suivant = temp->suivant;
                temp->precedent = temp->suivant;
                temp->suivant->suivant = temp;
                temp->suivant = temp2;
                i++;

            }
            temp = temp->suivant;
        }

    }while ( i );

    do{
        i = 0;
        temp = a;
        while( temp->suivant ){
            if( temp->y != '-' && temp->indicey > temp->suivant->indicey ){
                temp2 = temp->suivant->suivant;
                if(temp->precedent->suivant) temp->precedent->suivant = temp->suivant;
                temp->precedent->suivant->precedent->suivant = temp->suivant;
                temp->precedent = temp->suivant;
                temp->suivant->suivant = temp;
                temp->suivant = temp2;
                i++;

            }
            temp = temp->suivant;
        }

    }while ( i );

}
