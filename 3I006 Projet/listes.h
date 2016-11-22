typedef struct liste{
    char x;
    char y;
    int poids;
    struct liste * precedent;
    struct liste * suivant;
}Liste;

Liste * nouvelleListe( char a , char b , Liste * precedent , Liste * suivant );

Liste * dernier( Liste * a );

Liste* concatener( Liste * a , Liste * b );

void coupe( Liste *  a);
