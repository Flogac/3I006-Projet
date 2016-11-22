#include <stdio.h>
#include <stdlib.h>
#include "algo_reponse.h"
#include "utilitaire.h"

char * X2a ;
char* Y2a;
char ** F2a;
char * X2b;
char* Y2b ;
char ** F2b;
char * X;
char * Y;
int dxy;
int dgap;
int tailleX;
int tailleY;

// Question 4.1

//Lis une l'instance de chaînes de nucléotides dans le fichier nomfichier et les store dans deux tableaux de char, et leurs tailles dans deux int.
//Retourne 1 si la lecture est réussie, 2 s'il n'y a pas d'instance et 0 en cas de nom de variable absente.
//Retourne -1 en cas de problème de mémoire.
int lectureTableau( char * nomfichier , char ** premiereListe , char ** secondeListe , int * taillePremiereListe, int * tailleSecondeListe){

    //Vérification des adresses.
    if( !nomfichier ) return 0;
    if( !premiereListe ) return 0;
    if( !secondeListe ) return 0;
    if( !taillePremiereListe )return 0;
    if( !tailleSecondeListe ) return 0;

    FILE * f;
    char buffer[256];
    int i,j;

    if( initialiserTableau( buffer , 256) == 0 ){
        printf( "Probleme à l'execution de la fonction: lectureTableau.\n");
        return -1;
    }

    f = fopen( nomfichier , "r");
    if( !fgets( buffer , 256 , f )){
        printf( "Probleme à l'execution de la fonction: lectureTableau.\n");
        fclose( f );
        return -1;
    }
    //lecture de la chaîne de caractère.
    i = 1;
    while( buffer[i] != '-' ) i++;
    taillePremiereListe = 0;
    for( j = i ; j >=0 ; j-- ) *taillePremiereListe += ( buffer[j] - 48 ) * 10 * i--;

    if( initialiserTableau( buffer , 256) == 0){
        printf( "Probleme à l'execution de la fonction: lectureTableau.\n");
        fclose( f );
        return -1;
    }

    f = fopen( nomfichier , "r");
    if( !fgets( buffer , 256 , f )){
        printf( "Probleme à l'execution de la fonction: lectureTableau.\n");
        fclose( f );
        return -1;
    }
    //lecture de la chaîne de caractère.
    i = 1;
    while( buffer[i++] != '-' );
    tailleSecondeListe = 0;
    for( j = i ; j >=0 ; j-- ) *tailleSecondeListe += ( buffer[j] - 48 ) * 10 * i--;

    //initialisation des tableaux de liste
    *premiereListe = ( char * ) malloc ( sizeof( char ) * (*taillePremiereListe));
    *secondeListe = ( char * ) malloc ( sizeof( char ) * (*tailleSecondeListe));

    //remplissage premier tableau
    i = *taillePremiereListe;
    for( j = 0 ; j < i ; j++ ){
        if( !fgets( buffer , 1 , f )){
            printf( "Probleme à l'execution de la fonction: lectureTableau.\n");
            fclose( f );
            free (*premiereListe);
            free (*secondeListe);
            return -1;
        }
        *premiereListe[j] = buffer[0];
    }

    //remplissage second tableau
    i = *taillePremiereListe;
    for( j = 0 ; j < i ; j++ ){
        if( !fgets( buffer , 1 , f )){
            printf( "Probleme à l'execution de la fonction: lectureTableau.\n");
            fclose( f );
            free (*premiereListe);
            free (*secondeListe);
            return -1;
        }
        *secondeListe[j] = buffer[0];
    }

    return 1;

}

//Question 4.2

/*
Soit COUPE (liste x) l’algorithme qui permet de supprimer le dernier élement d’une liste.
Soit DERNIER(liste x) l’algorithme qui renvoie le dernier élement d’une liste.
Soit TAILLE(liste x) l’algorithme qui renvoie le nombre d’élements d’une liste.
Algorithme : COUT1
Entrées : x : liste de caractères, y : liste de caractères, dxy : entier, dgap : entier
cmin <-0, c1<-0,  c2<-0,  c3<-0
si TAILLE(x)=0 faire
    cmin <- TAILLE(y)*dgap ;
sinon faire
    si TAILLE(y)=0 faire
         cmin <- TAILLE(x)*dgap ;
         sinon faire
             si DERNIER (x) = DERNIER (y) faire
                  cmin<-COUT1 (COUPE (x), COUPE(y)) ;
             sinon faire
                   c1<-COUT1 (COUPE (x), COUPE(y)) + dxy;
                   c2<-COUT1 (x, COUPE(y)) + dgap ;
                   c3<-COUT1 (COUPE(x), y) + dgap ;
                   cmin<-min(c1,c2,c3) ;
Retourner cmin 
*/

int COUT1( char * tabX , char * tabY , int tailleX , int tailleY , int dxy , int dgap ){
    if( !tabX ) return 0;
    if( !tabY ) return 0;
    if( !dxy && !dgap ) return 0; // Le coût minimum sera toujours nul.

    int cmin = 0;

    if( !tailleX ){
        cmin = tailleY * dgap;
    }else if( !tailleY ){
        cmin = tailleX * dgap;
    }else if( tabX[tailleX] == tabY[tailleY] ){
        cmin = COUT1( tabX, tabY , tailleX - 1 , tailleY - 1 , dxy , dgap );
    }else cmin = min3(  dxy + COUT1( tabX, tabY , tailleX - 1 , tailleY - 1 , dxy , dgap ),
                        dgap + COUT1( tabX, tabY , tailleX , tailleY - 1 , dxy , dgap ),
                        dgap + COUT1( tabX, tabY , tailleX - 1 , tailleY , dxy , dgap ));

    return cmin;
}

/*
Algorithme : SOL1
Entrées : x : tableau de caractères, y : liste de caractères , dxy : entier, dgap : entier
align<-‘ ’(liste vide), cmin <-0, c1<-0,  c2<-0,  c3<-0,
Tant que TAILLE(x)>0 et TAILLE(y)>0 faire
     si DERNIER (x) = DERNIER (y) faire
         x<-COUPE (x) ;
         y<- COUPE(y) ;
         align<-AJOUT(align,’DERNIER(x), DERNIER(y)’) ;
     sinon faire
         c1<-F(x,y)+ dxy;
         c2<-F(x, COUPE(y)) + dgap ;
         c3<-F (COUPE(x), y) + dgap ;
         cmin<-min(c1,c2,c3) ;
         si cmin=c1 faire
                x<-COUPE (x) ;
                y<- COUPE(y) ;
                align<-AJOUT(align,’DERNIER(x), DERNIER(y)’);
         sinon faire
               si cmin=c2 faire
                     y<- COUPE(y) ;
                sinon faire
                     x<-COUPE (x) ;
(Retourner align ;).
*/
Liste * SOL1( char  * x , int taillex , char * y , int tailley, int dxy , int dgap ){
    Liste * align = NULL;
    int cmin = 0 , c1 , c2 , c3;
    while( taillex && tailley ){
        if( x[taillex - 1] == y[tailley - 1] ){
            taillex--;
            tailley--;
            if( align ){
                concatener( &align , nouvelleListe( x[taillex-1] , y[tailley-1] , NULL , NULL ) );
            }else{
                align = nouvelleListe( x[taillex] , y[tailley-1] , NULL, NULL );
                align->precedent = align;
            }
        } else {
            c1 = COUT1( x , y , taillex , tailley , dxy , dgap ) + dxy ;
            c2 = COUT1( x , y , taillex , tailley-1 , dxy , dgap ) + dxy ;
            c3 = COUT1( x , y , taillex-1 , tailley , dxy , dgap ) + dxy ;
            cmin = min3( c1 , c2 , c3 );
            if( cmin == c1 ){
                taillex--;
                tailley--;
                if( align ){
                    concatener( &align , nouvelleListe( x[taillex-1] , y[tailley-1] , NULL , NULL ) );
                }else{
                    align = nouvelleListe( x[taillex] , y[tailley-1] , NULL, NULL );
                    align->precedent = align;
                }
            }else if( cmin == c2 ){
                tailley--;
            }else taillex--;
        }
    }
    return align;
}

/*
cout initialisé à 0 partout et de taille taillex * tailley.
*/
int COUT2intel( char * tabX , char * tabY , int tailleX , int tailleY , int dxy , int dgap , int *** cout , int THEi , int THEj ){
    if( !tabX ) return 0;
    if( !tabY ) return 0;
    if( !cout ) return 0;
    if( !dxy && !dgap ) return 0; // Le coût minimum sera toujours nul.

    int i , j;

    for( i = THEi ; i < tailleX ; i++ ) for( j = THEj ; j < tailleY ; j++ ){
        if( !i ){
            if( j ) *cout[i][j] = dgap;

        }else{
            if( !j ){ *cout[i][j] = *cout[i][j-1] + dgap;}
            else *cout[i][j] = min3( *cout[i][j-1] + dgap , *cout[i-1][j] + dgap , *cout[i-1][j-1] + dxy );
        }
    }

    return *cout[tailleX-1][tailleY-1];
}

/*

*/
int COUT2( char * tabX , char * tabY , int tailleX , int tailleY , int dxy , int dgap , int THEi , int THEj ){
    if( !tabX ) return 0;
    if( !tabY ) return 0;
    if( !dxy && !dgap ) return 0; // Le coût minimum sera toujours nul.

    int i , j , cout[tailleX][tailleY];

    for( i = 0 ; i < tailleX ; i++ ) initialiserTableauInt( cout[i] , tailleY ); // Met toutes les cases à 0.

    for( i = THEi ; i < tailleX ; i++ ) for( j = THEj ; j < tailleY ; j++ ){
        if( !i ){
            if( j ) cout[i][j] = dgap;

        }else{
            if( !j ){ cout[i][j] = cout[i][j-1] + dgap;}
            else cout[i][j] = min3( cout[i][j-1] + dgap , cout[i-1][j] + dgap , cout[i-1][j-1] + dxy );
        }
    }

    return cout[tailleX-1][tailleY-1];
}

int COUT2BIS( char * tabX , char * tabY , int tailleX , int tailleY , int dxy , int dgap , int THEi , int THEj ){
    if( !tabX ) return 0;
    if( !tabY ) return 0;
    if( !dxy && !dgap ) return 0; // Le coût minimum sera toujours nul.

    int i , j , cout[tailleX][tailleY];

    for( i = 0 ; i < tailleX ; i++ ) initialiserTableauInt( cout[i] , tailleY ); // Met toutes les cases à 0.

    for( i = 0 ; i < tailleX ; i++ ) for( j = 0 ; j < tailleY ; j++ ){
        if( !i ){
            if( j ) cout[i][j] = dgap;

        }else{
            if( !j ){ cout[i][j] = cout[i][j-1] + dgap;}
            else cout[i][j] = min3( cout[i][j-1] + dgap , cout[i-1][j] + dgap , cout[i-1][j-1] + dxy );
        }
    }

    return cout[THEi][THEj];
}

// nécessite un appel de COUT2intel
int COUT2BISintel( int i , int j , int *** cout){
    return *cout[i][j];
}

/*
X2a: tableau de caract`eres de taille 3
Y 2a: tableau de caract`eres de taille n + 1
F2a: matrice de caract`eres de taille 3 × (n + 1)
X2b: tableau de caract`eres de taille m + 1
Y 2b: tableau de caract`eres de taille 3
F2b: matrice de caract`eres de taille (m + 1) × 3

Fonction SOL2(k1, l1, k2, l2, L)
    Si k2 − k1 > 0 ou l2 − l1 > 0 Alors
        Si k2 − k1 <= 2 Alors
            Pour i de k1 `a k2 Faire X2a[i − k1] ← X[i]
            Pour j de l1 `a l2 Faire Y 2a[j − l1] ← Y [j]
                Utiliser le code de la partie 1 pour X2a et Y 2a en utilisant la matrice F2a
                Concat´ener le chemin obtenu dans L.
                Retourner F2b[k2 − k1, l2 − l1]
        Sinon
            Si l2 − l1 <= 2 Alors
                Pour i de k1 `a k2 Faire X2b[i − k1] ← X[i]
                    Pour j de l1 `a l2 Faire Y 2b[j − l1] ← Y [j]
                        Utiliser le code de la partie 1 pour X2b et Y 2b en utilisant la matrice F2b
                        Concat´ener le chemin obtenu dans L.
                        Retourner F2b[k2 − k1, l2 − l1]
            Sinon
                j ← l1 + arrsup( (l2−l1)/ 2 )
                i ∗ ← k1
                valmin ← COUT2(k1, j)+COUT2BIS(k1, j)
                Pour i de k1 + 1 `a k2 Faire
                    val=COUT2(i, j)+COUT2BIS(i, j)
                    Si valmin > val Alors
                        valmin ← val
                        i∗ ← i
                    FinSi
                FinPour
                Retourner SOL2(k1, l1, i*, j, L) + SOL2(i*, j, k2, l2, L)
*/
void SOL2(int k1 , int l1 , int k2 , int l2 , Liste ** L ){
    int i , j;
    int k;
    int valmin;
    int val;

    if( k2 - k1 > 0 || l2-l1 > 0 ){
        if( k2 - k1 <= 2 ){
            for( i = k1 ; i <= k2 ; i++) X2a[i - k1] = X[i];
            for( i = l1 ; i <= l2 ; i++) Y2a[i - k1] = Y[i];
            concatener( L , SOL1( X2a , k2 - k1 +1 , Y2a , l2 - l1 +1 , dxy , dgap ) );
            //return F2b[k2-k1 ][ l2-l1];
        }else{
            if( l2-l1 <= 2 ){
                    for( i = k1 ; i <= k2 ; i++ ) X2b[i - k1 ] = X[i];
                    for( i = l1 ; i <= l2 ; i++ ) Y2b[i - k1 ] = Y[i];
                    concatener( L , SOL1( X2a , k2 - k1 +1 , Y2a , l2 - l1 +1 , dxy , dgap ) );
                    //return F2b[ k2-k1 ][ l2 -l1];
            }else{
                j = l1 +((l2-l1+1)/2);
                k = k1;
                valmin = COUT2( X , Y , tailleX , tailleY , dxy , dgap , k1 , j ) + COUT2BIS( X , Y , tailleX , tailleY , dxy , dgap , k1 , j) ;
                for( i = k1+1 ; i<= k2 ; i++){
                    val = COUT2( X , Y , tailleX , tailleY , dxy , dgap , i , j ) + COUT2BIS( X , Y , tailleX , tailleY , dxy , dgap , i , j) ;
                    if( valmin > val ){
                        valmin = val;
                        k = i;
                    }
                }
                SOL2(k1, l1, k, j, L);
                SOL2(k, j, k2, l2, L);
            }

        }
    }
}


void appelSOL2( char ** X2ae , char** Y2ae , char *** F2ae , char ** X2be , char** Y2be , char *** F2be , int k1 , int l1 , int k2 , int l2 , Liste * L , char ** Xe , char ** Ye , int dxye , int dgape , int tailleXe , int tailleYe ){
 X2a = *X2ae ;
 Y2a = *Y2ae ;
 F2a = *F2ae ;
 X2b = *X2be ;
 Y2b = *Y2be ;
 F2b = *F2be ;
 X = *Xe;
 Y = *Ye;
dxy = dxye;
dgap = dgape;
tailleX = tailleXe;
tailleY = tailleYe;

SOL2( k1 , l1 , k2 , l2 , L );
}
