#include "listes.h"

Liste * nouvelleListe( char a , char b , Liste * precedent , Liste * suivant ){
    Liste * retour = ( Liste * ) malloc ( sizeof( Liste ) );
    retour->x = a;
    retour->y = b;
    retour->precedent = precedent;
    retour->suivant = suivant;
    retour->poids = 0;
    return retour;
}

Liste * dernier( Liste * a ){
    if( !a ) return NULL;
    return a->precedent;
}

void concatener( Liste * a , Liste * b ){
    if( !a ) return;
    if( !b ) return;
    Liste * c = dernier( a );
    if( !c ) return;
    c->suivant = b;
    a->precedent = dernier(b);
    b->precedent = c;
}

void coupe( Liste *  a){
    if(!a) return;
    Liste * b = a->precedent->precedent;
    free( a->precedent );
    a->precedent = b;
}
