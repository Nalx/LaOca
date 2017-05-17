/*******************************************
*
* @Arxiu: Grafics.h
* @Finalitat: 
* @Autor/s: Àlex Cordón Vila i Sergio Gonzalez Mendoza
* @Data:10/3/2013
*
********************************************/
#ifndef _GRAFICS_H
#define _GRAFICS_H
#include "logica.h"
//#include "grafics.h"
#include <string.h>
#include <stdlib.h>
#include <allegro.h>
#include <stdio.h>
void entorn(int nNumJugadors,DadesJugadors astJugador[4],int nDaus,int anValorsdau[4],int torn,Caselles astCasella[MAXC],int nJugadorsFitxer,JugadorFinal astDades[5]);
void entornRanking(int nJugadorsFitxer,JugadorFinal astDades[5]);
void entornFons();
void entornTirada();
void entornCaselles(Caselles astCasella[MAXC]);
void entornFinal();
void entornContornCaselles();
void pintaFitxesInicials(int nNumJugadors,Caselles astCasella[MAXC],DadesJugadors astJugador[4]);
void OrdrenaJugadors(DadesJugadors astJugador[4],int nNumJugadors,int anValorsdau[4]);
void entornOrdre(DadesJugadors astJugador[4],int nNumJugadors,int torn);
void pintaFitxesMoviment(int nNumJugadors,Caselles astCasella[MAXC],int torn,DadesJugadors astJugador[4]);
void pintaTirada(DadesJugadors astJugador[4],int torn);
void esborraFitxaMoviment(int nNumJugadors,Caselles astCasella[MAXC],int torn,DadesJugadors astJugador[4]);


#endif
