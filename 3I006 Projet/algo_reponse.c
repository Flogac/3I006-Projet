#include <stdio.h>
#include <stdlib.h>
#include "algo_reponse.h"
#include "utilitaire.h"

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
    while( buffer[i] != '-' ) i++;
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

int COUT1( int * tabX , int * tabY , int tailleX , int tailleY , int dxy , int dgap ){
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
