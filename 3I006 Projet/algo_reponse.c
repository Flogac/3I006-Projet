#include <stdio.h>
#include "utilitaire.h"

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
    taillePremiereListe = 0;
    for( j = i ; j >=0 ; j-- ) *tailleSecondeListe += ( buffer[j] - 48 ) * 10 * i--;

    i = *taillePremiereListe;
    for( j = 0 ; j < i ; j++ ){

    }

    return 1;

}
