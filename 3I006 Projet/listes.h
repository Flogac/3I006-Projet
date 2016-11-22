typedef struct liste{
    char x;
    int indicex;
    char y;
    int indicey;
    int poids;
    struct liste * precedent;
    struct liste * suivant;
}Liste;

Liste * nouvelleListe( char a , char b , Liste * precedent , Liste * suivant , int indicea , int indiceb );

Liste * dernier( Liste * a );

void concatener( Liste ** a , Liste * b );

void coupe( Liste *  a);

void trie( Liste * a );
