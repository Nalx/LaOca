/*******************************************
*
* @Arxiu: Logica.h
* @Finalitat: Procediments/funcions i tipus estructurats de lògica  
* @Autor/s: Àlex Cordón Vila i Sergio Gonzalez Mendoza
* @Data:10/3/2013
*
********************************************/
#ifndef _LOGICA_H
#define _LOGICA_H

#include "grafics.h"
#include <stdio.h>
#include <allegro.h>
#include <time.h>
#include <string.h>

#define MAXC 98

typedef struct{
    //Hi guardem el nom de cada jugador
    char cNom[30];
    //Hi guardem el valor de la casella on es troben els jugadors
    int nNumCasella;
    //Hi guardem el valor del dau tirat en cada torn
    int nValorsDeDau;
    //Comptador de tirades per a cada jugador
    int nTirades;
    //Torns que porta esperant
    int nPou;
}DadesJugadors;
typedef struct{
    //Hi guardem les coordenades de les caselles
    int nCoordenades[2];
    //Hi guardem el color de casella (Gris:7,blanc:15,negre:0,taronja:6)
    int nColor;
    //Hi guardem el valor enter de la posició entre 1 i MAXC
    int nNumPosicio;  
    //Hi guardem els torns de penalització al caure a la casella
    int nTornsBucle;  
}Caselles;
typedef struct{
    //Hi guardem el valor del primer dau
    int nDau1;
    //Hi guardem el valor del segon dau
    int nDau2;
}Daus;
typedef struct{
    //Hi guardem el nom del jugador guanyador
    char cNom[30];
    //Hi guardem el nombre de tirades que ha fet per guanyar la partida
    int nTirades;
}JugadorFinal;

void infoteclat (int *nNumJugadors,DadesJugadors astJugador[4],int anValorsdau[4],Caselles astCasella[MAXC]);
void nombreJugadors (int *nJugadors);
void nomJugadors (int nJugadors,DadesJugadors astJugador[4] );
void modeDeJoc (Caselles astCasella[MAXC],DadesJugadors astJugador[4]);
int dauSortida(int nJugadors,DadesJugadors astJugador[4],int anValorsdau[4]);
void tecla(DadesJugadors astJugador[4],int *nDaus,int nNumJugadors,int *torn,Caselles astCasella[MAXC],JugadorFinal astDades[5]);
void dausTirada(int *nDaus,DadesJugadors astJugador[4],int torn,int nNumJugadors,Caselles astCasella[MAXC],int *nTiradesTotals,Daus valor[1000]);
void mouTorn(int *torn,int nNumJugadors,Caselles astCasella[MAXC],DadesJugadors astJugador[4]);
void finalDePartida(DadesJugadors astJugador[4],int torn,int *sortir,Daus valor[1000],int nTiradesTotals,JugadorFinal astDades[5]);
int inicialitzaVariables(DadesJugadors astJugador[4],Caselles astCasella[MAXC],int nMode,char sNomFitxer[30]);
void casellaFuncio(Caselles astCasella[MAXC],int torn,DadesJugadors astJugador[4],int nNumJugadors);
void casellaBucle(Caselles astCasella[MAXC],int torn,DadesJugadors astJugador[4],int nNumJugadors);
void casellaCore(Caselles astCasella[MAXC],int torn,DadesJugadors astJugador[4],int nNumJugadors);
int fitxerConfiguracio(Caselles astCasellaFitxer[MAXC],char sNomFitxer[30]);
int llegirRanquing(JugadorFinal astDades[5]);
void escriuRanquing(JugadorFinal stGuanyador,JugadorFinal astDades[5]);
int ordenaJugadors(JugadorFinal astDades[5],JugadorFinal stGuanyador,int j);
void fitxerMoviment(Daus valor[1000],int nTiradesTotals);


#endif
