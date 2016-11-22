#include "listes.h"

int lectureTableau( char * nomfichier , char ** premiereListe , char ** secondeListe , int * taillePremiereListe, int * tailleSecondeListe);

void afficherTailleRaisonnable( char * tabX , char * tabY , int tailleX , int tailleY );

int COUT1( char * tabX , char * tabY , int tailleX , int tailleY , int dxy , int dgap );

Liste * SOL1( char  * x , int taillex , char * y , int tailley, int dxy , int dgap );

void afficherListe( Liste * L );

int COUT2intel( char * tabX , char * tabY , int tailleX , int tailleY , int dxy , int dgap , int *** cout , int THEi , int THEj );

int COUT2( char * tabX , char * tabY , int tailleX , int tailleY , int dxy , int dgap , int THEi , int THEj );

int COUT2BIS( char * tabX , char * tabY , int tailleX , int tailleY , int dxy , int dgap , int THEi , int THEj );

int COUT2BISintel( int i , int j , int *** cout);

void SOL2(int k1 , int l1 , int k2 , int l2 , Liste ** L );

void appelSOL2( char * X2ae , char* Y2ae , char ** F2ae , char * X2be , char* Y2be , char ** F2be , int k1 , int l1 , int k2 , int l2 , Liste ** L , char * Xe , char * Ye , int dxye , int dgape , int tailleXe , int tailleYe );
