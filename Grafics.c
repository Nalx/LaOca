/*******************************************
*
* @Arxiu: Grafics.c
* @Finalitat: Implementacións de funcions i procediments del modul de gràfics
* @Autor/s: Àlex Cordón Vila i Sergio Gonzalez Mendoza
* @Data:10/3/2013
*
********************************************/

//Sistema
#include <stdlib.h>
//Propies
#include "grafics.h"
#include "logica.h"

//Pintem tot l'entorn del tauler
void entorn (int nNumJugadors,DadesJugadors astJugador[4],int nDaus,int anValorsdau[4],int torn,Caselles astCasella[MAXC],int nJugadorsFitxer,JugadorFinal astDades[5]) {
    entornTirada (); 
    entornCaselles (astCasella);
    entornFinal ();
    OrdrenaJugadors(astJugador,nNumJugadors,anValorsdau);
    pintaTirada(astJugador,torn);
    entornOrdre(astJugador,nNumJugadors,torn);
    entornRanking (nJugadorsFitxer,astDades);
    entornContornCaselles();
}
//Entorn on pintem les tirades
void entornTirada(){
    rectfill(screen,600,0,800,400,15);   
    rect(screen,600,0,800,400,0);
    rect(screen,601,1,799,399,0);
    textprintf_ex(screen, font,615,20,0,-1,"Tirada");
    line(screen,615,30,665,30,0);
    textprintf_ex(screen, font,615,110,0,-1,"Ordre");
    line(screen,615,120,655,120,0);
    textprintf_ex(screen, font,615,260,0,-1,"Llegenda Caselles ");
    line(screen,615,270,750,270,0);
    rectfill(screen,620,280,635,290,15);
    rect(screen,620,280,635,290,0);
    textprintf_ex(screen, font,640,280,0,-1,"Tipus Normal");
    rectfill(screen,620,300,635,310,7);
    rect(screen,620,300,635,310,0);
    textprintf_ex(screen, font,640,300,0,-1,"Tipus Funcio");
    rectfill(screen,620,320,635,330,6);
    rect(screen,620,320,635,330,0);
    textprintf_ex(screen, font,640,320,0,-1,"Tipus Bucle Infinit");
    rectfill(screen,620,340,635,350,0);
    rect(screen,620,340,635,350,0);
    textprintf_ex(screen, font,640,340,0,-1,"Tipus Core Dumped");
    rectfill(screen,620,360,635,370,8);
    rect(screen,620,360,635,370,0);
    textprintf_ex(screen, font,640,360,0,-1,"Tipus Final");
}
//Funcio que pinta el cuadre on es mostren els rankings
void entornRanking(int nJugadorsFitxer,JugadorFinal astDades[5]){
    int nLlargada;
    int i=0;
    int nMoureY=0;
    //Dibuix dels quadres que delimiten l'entorn del rànquing
    rectfill(screen,600,400,800,600,15);    
    rect(screen,600,400,800,600,0);
    rect(screen,601,401,799,599,0);
    textprintf_ex(screen, font,615,410,0,-1,"Rankings");
    line(screen,615,420,680,420,0);
    //Mostra per pantalla gràfica un missatge quan no hi ha cap jugador al rànquing
    if (nJugadorsFitxer==0){
        textprintf_ex(screen, font,615,440,0,-1,"No hi ha partides"); 
        textprintf_ex(screen, font,615,455,0,-1,"anteriors.");  
    }else{
        //Pintem per pantalla gràfica el nom dels jugadors
        while (i<nJugadorsFitxer){
            //Elimina el # de final de nom
            nLlargada=strlen(astDades[i].cNom);
            astDades[i].cNom[nLlargada-1]='\0'; 
            textprintf_ex(screen, font,615,440+nMoureY,0,-1,"%s" " - " "%d" " tir.",astDades[i].cNom, astDades[i].nTirades);    
            i++;
            nMoureY=nMoureY+20;
        }
    }
}
//Pintem la cuadricula amb totes les caselles
void entornCaselles(Caselles astCasella[MAXC]){
    int nCotaX=0;
    int nCotaY=0;
    int i=0; 
    //Inicialització de les coordenades inicials de les caselles
    int x=0;
    int y=540;
    while (i<MAXC){
        while(x+nCotaX<600){
            astCasella[i].nCoordenades[0]=x;
            astCasella[i].nCoordenades[1]=y;
            if (i==0){
                x=x+120;
            }else{
                x=x+60;
            }
            i=i+1;
        }
        x=x-60;
        y=y-60;
        while(y-nCotaY>0){
            astCasella[i].nCoordenades[0]=x;
            astCasella[i].nCoordenades[1]=y;
            y=y-60;
            i=i+1;           
        }
        while(x-nCotaX>0){
            astCasella[i].nCoordenades[0]=x;
            astCasella[i].nCoordenades[1]=y;
            x=x-60;
            i=i+1;
        }
        nCotaY=nCotaY+60;
        while(y+nCotaY<600){
            astCasella[i].nCoordenades[0]=x;
            astCasella[i].nCoordenades[1]=y;
            y=y+60;
            i=i+1;    
        }
        x=x+60;
        y=y-60;
        nCotaX=nCotaX+60;
    
    }
    i=0;
    //Pintem les caselles (Posició+color+numero)
    while (i<MAXC){
        if(i==0){
            rectfill(screen,astCasella[i].nCoordenades[0],astCasella[i].nCoordenades[1],astCasella[i].nCoordenades[0]+120,astCasella[i].nCoordenades[1]+60,astCasella[i].nColor);    
            //astCasella[i].nColor=0;
            rect(screen,astCasella[i].nCoordenades[0],astCasella[i].nCoordenades[1],astCasella[i].nCoordenades[0]+120,astCasella[i].nCoordenades[1]+60,0);
            textprintf_ex(screen,font,astCasella[i].nCoordenades[0]+5,astCasella[i].nCoordenades[1]+5,4,-1,"%s","Sortida");
            i++;         
         }else{
            rectfill(screen,astCasella[i].nCoordenades[0],astCasella[i].nCoordenades[1],astCasella[i].nCoordenades[0]+60,astCasella[i].nCoordenades[1]+60,astCasella[i].nColor);    
            //astCasella[i].nColor=0;
            rect(screen,astCasella[i].nCoordenades[0],astCasella[i].nCoordenades[1],astCasella[i].nCoordenades[0]+60,astCasella[i].nCoordenades[1]+60,0);
            textprintf_ex(screen,font,astCasella[i].nCoordenades[0]+5,astCasella[i].nCoordenades[1]+5,4,-1,"%d",i);
            i++;
         }
     }
} 
//Pintem el cuadre gris equivalent a la casella final 95.  
void entornFinal(){
    rectfill(screen,240,240,359,359,8);    
    rect(screen,240,240,360,360,0);
    textprintf_ex(screen, font,245,245,15,-1,"Final");
}
//Funcio que pinta el contorn separador de les caselles
void entornContornCaselles(){
    int i=0;
    
    int nX1=0;
    int nY1=539;
    int nX2=539;
    int nY2=539;
    while (i<4){  
        line(screen,nX1,nY1,nX2,nY2,8);
        nX1=nX1+60;
        nY1=nY1-60;
        nX2=nX2-60;
        nY2=nY2-60;
        i++;
    }
    nX1=59;
    nY1=59;
    nX2=59;
    nY2=479;
    i=0;
    while (i<4){  
        line(screen,nX1,nY1,nX2,nY2,8);
        nX1=nX1+60;
        nY1=nY1+60;
        nX2=nX2+60;
        nY2=nY2-60;
        i++;
    }
   nX1=599;
    nY1=0;
    nX2=599;
    nY2=599;
    i=0;
    while (i<=4){  
        line(screen,nX1,nY1,nX2,nY2,8);
        nX1=nX1-60;
        nY1=nY1+60;
        nX2=nX2-60;
        nY2=nY2-60;
        i++;
    }
    nX1=59;
    nY1=59;
    nX2=539;
    nY2=59;
    i=0;
    while (i<4){  
        line(screen,nX1,nY1,nX2,nY2,8);
        nX1=nX1+60;
        nY1=nY1+60;
        nX2=nX2-60;
        nY2=nY2+60;
        i++;
    }
}
//En aquesta funció mostrem per pantalla gràfica el nom de tots els jugadors en l'ordre especificat de tirades
void OrdrenaJugadors(DadesJugadors astJugador[4],int nNumJugadors,int anValorsdau[4]){
    //Utilitzem i per controlar el bucle for per mostrar els noms el funció del nombre de jugadors
    int nGran;
    int nGranPos=0;
    int i=0;
    int k=0;
    int n=0;
    int j=0;
    DadesJugadors astAuxordre[4];
    for (i=0;i<nNumJugadors;i++) {
        nGran=0;
        j=0;
        while (j<nNumJugadors){          
            if(anValorsdau[j]>nGran){
                nGran=anValorsdau[j];
                nGranPos=j;
            }
            j++;
        }
        strcpy(astAuxordre[i].cNom, astJugador[nGranPos].cNom);
        anValorsdau[nGranPos]=-1;
    }
    i=0;
    //Copiem l'ordre un cop tirats els daus 
    for (i=0;i<nNumJugadors;i++){
        strcpy(astJugador[i].cNom,astAuxordre[i].cNom);
    }
}
void entornOrdre(DadesJugadors astJugador[4],int nNumJugadors,int torn){
    //El recuadre blanc esborra les dades anteriors
    int i=0;
    int y=0;
    rectfill(screen,625,132,790,250,15);
    switch(torn){
        case 0:
            if (nNumJugadors==2){
                circlefill(screen,615,137,4,2);
                circle(screen,615,137,4,0);
                circlefill(screen,615,157,4,1);
                circle(screen,615,157,4,0);
                textprintf_ex(screen,font,625,135,0,-1,"%s - %d",astJugador[0].cNom,astJugador[0].nTirades);
                textprintf_ex(screen,font,625,155,0,-1,"%s - %d",astJugador[1].cNom,astJugador[1].nTirades);
            }
            if(nNumJugadors==3){
                circlefill(screen,615,137,4,2);
                circle(screen,615,137,4,0);
                circlefill(screen,615,157,4,1);
                circle(screen,615,157,4,0);
                circlefill(screen,615,177,4,4);
                circle(screen,615,177,4,0);
                textprintf_ex(screen,font,625,135,0,-1,"%s - %d",astJugador[0].cNom,astJugador[0].nTirades);
                textprintf_ex(screen,font,625,155,0,-1,"%s - %d",astJugador[1].cNom,astJugador[1].nTirades);
                textprintf_ex(screen,font,625,175,0,-1,"%s - %d",astJugador[2].cNom,astJugador[2].nTirades); 
            }
            if(nNumJugadors==4){
                circlefill(screen,615,137,4,2);
                circle(screen,615,137,4,0);
                circlefill(screen,615,157,4,1);
                circle(screen,615,157,4,0);
                circlefill(screen,615,177,4,4);
                circle(screen,615,177,4,0);
                circlefill(screen,615,197,4,14);
                circle(screen,615,197,4,0);
                textprintf_ex(screen,font,625,135,0,-1,"%s - %d",astJugador[0].cNom,astJugador[0].nTirades);
                textprintf_ex(screen,font,625,155,0,-1,"%s - %d",astJugador[1].cNom,astJugador[1].nTirades);
                textprintf_ex(screen,font,625,175,0,-1,"%s - %d",astJugador[2].cNom,astJugador[2].nTirades);
                textprintf_ex(screen,font,625,195,0,-1,"%s - %d",astJugador[3].cNom,astJugador[3].nTirades);  
            }
        break;
        case 1:
            if (nNumJugadors==2 ){
                circlefill(screen,615,137,4,1);  
                circlefill(screen,615,157,4,2);
                circle(screen,615,137,4,0);
                circle(screen,615,157,4,0);
                textprintf_ex(screen,font,625,135,0,-1,"%s - %d",astJugador[1].cNom,astJugador[1].nTirades);
                textprintf_ex(screen,font,625,155,0,-1,"%s - %d",astJugador[0].cNom,astJugador[0].nTirades);
            }
            if(nNumJugadors==3){
                circlefill(screen,615,137,4,1);
                circle(screen,615,137,4,0);
                circlefill(screen,615,157,4,4);
                circle(screen,615,157,4,0);
                circlefill(screen,615,177,4,2);
                circle(screen,615,177,4,0);
                textprintf_ex(screen,font,625,135,0,-1,"%s - %d",astJugador[1].cNom,astJugador[1].nTirades);
                textprintf_ex(screen,font,625,155,0,-1,"%s - %d",astJugador[2].cNom,astJugador[2].nTirades);
                textprintf_ex(screen,font,625,175,0,-1,"%s - %d",astJugador[0].cNom,astJugador[0].nTirades); 
            }
            if(nNumJugadors==4){
                circlefill(screen,615,137,4,1);
                circle(screen,615,137,4,0);
                circlefill(screen,615,157,4,4);
                circle(screen,615,157,4,0);
                circlefill(screen,615,177,4,14);
                circle(screen,615,177,4,0);
                circlefill(screen,615,197,4,2);
                circle(screen,615,197,4,0);
                textprintf_ex(screen,font,625,135,0,-1,"%s - %d",astJugador[1].cNom,astJugador[1].nTirades);
                textprintf_ex(screen,font,625,155,0,-1,"%s - %d",astJugador[2].cNom,astJugador[2].nTirades);
                textprintf_ex(screen,font,625,175,0,-1,"%s - %d",astJugador[3].cNom,astJugador[3].nTirades);
                textprintf_ex(screen,font,625,195,0,-1,"%s - %d",astJugador[0].cNom,astJugador[0].nTirades); 
            } 
        break;
        case 2:
            if(nNumJugadors==3){
                circlefill(screen,615,137,4,4);
                circle(screen,615,137,4,0);
                circlefill(screen,615,157,4,2);
                circle(screen,615,157,4,0);
                circlefill(screen,615,177,4,1);
                circle(screen,615,177,4,0);
                textprintf_ex(screen,font,625,135,0,-1,"%s - %d",astJugador[2].cNom,astJugador[2].nTirades);
                textprintf_ex(screen,font,625,155,0,-1,"%s - %d",astJugador[0].cNom,astJugador[0].nTirades);
                textprintf_ex(screen,font,625,175,0,-1,"%s - %d",astJugador[1].cNom,astJugador[1].nTirades); 
            }
            if(nNumJugadors==4){
                circlefill(screen,615,137,4,4);
                circle(screen,615,137,4,0);
                circlefill(screen,615,157,4,14);
                circle(screen,615,157,4,0);
                circlefill(screen,615,177,4,2);
                circle(screen,615,177,4,0);
                circlefill(screen,615,197,4,1);
                circle(screen,615,197,4,0);
                textprintf_ex(screen,font,625,135,0,-1,"%s - %d",astJugador[2].cNom,astJugador[2].nTirades);
                textprintf_ex(screen,font,625,155,0,-1,"%s - %d",astJugador[3].cNom,astJugador[3].nTirades);
                textprintf_ex(screen,font,625,175,0,-1,"%s - %d",astJugador[0].cNom,astJugador[0].nTirades); 
                textprintf_ex(screen,font,625,195,0,-1,"%s - %d",astJugador[1].cNom,astJugador[1].nTirades);
            }
        break;
        case 3:
            if(nNumJugadors==4){
                circlefill(screen,615,137,4,14);
                circle(screen,615,137,4,0);
                circlefill(screen,615,157,4,2);
                circle(screen,615,157,4,0);
                circlefill(screen,615,177,4,1);
                circle(screen,615,177,4,0);
                circlefill(screen,615,197,4,4);
                circle(screen,615,197,4,0);
                textprintf_ex(screen,font,625,135,0,-1,"%s - %d",astJugador[3].cNom,astJugador[3].nTirades);
                textprintf_ex(screen,font,625,155,0,-1,"%s - %d",astJugador[0].cNom,astJugador[0].nTirades);
                textprintf_ex(screen,font,625,175,0,-1,"%s - %d",astJugador[1].cNom,astJugador[1].nTirades); 
                textprintf_ex(screen,font,625,195,0,-1,"%s - %d",astJugador[2].cNom,astJugador[2].nTirades); 
            }
        break;
    }
   
}
//Funció que pinta el color i el nom del jugador que li toca tirar els daus
void pintaTirada(DadesJugadors astJugador[4],int torn){
    int nColor;
    rectfill(screen,605,35,780,55,15);
    textprintf_ex(screen,font,625,40,0,-1,"%s - %d",astJugador[torn].cNom,astJugador[torn].nTirades);
    switch(torn){
        case 0:
            nColor=2;      
        break;
        case 1:
            nColor=1;
        break;
        case 2:
            nColor=4;
        break;
        case 3:
            nColor=14;
        break;
    }
    circlefill(screen,615,45,4,nColor);
    circle(screen,615,45,4,0);
}
//Pinta la fitxa un cop s'han tirat els daus
void esborraFitxaMoviment(int nNumJugadors,Caselles astCasella[MAXC],int torn,DadesJugadors astJugador[4]){
    int x,y;
    int n;
    switch(torn){
        case 0:
            if(astJugador[torn].nNumCasella==0){
                x=80;
                y=40;
            }
            else{
                x=20;
                y=20;
            }
        break;
        case 1:
            if(astJugador[torn].nNumCasella==0){
                x=60;
                y=40;
            }else{
                x=40;
                y=20;
            }
        break;
        case 2:
            if(astJugador[torn].nNumCasella==0){
                x=40;
                y=40;
            }else{
                x=40;
                y=40;
            }
        break;
        case 3:
            if(astJugador[torn].nNumCasella==0){
                x=20;
                y=40;
            }else{
                x=20;
                y=40;
            }
            break;
                 
    }
    n=astJugador[torn].nNumCasella;
    circlefill(screen,astCasella[n].nCoordenades[0]+x,astCasella[n].nCoordenades[1]+y,8,astCasella[n].nColor);
}

void pintaFitxesInicials(int nNumJugadors,Caselles astCasella[MAXC],DadesJugadors astJugador[4]){
    int nTorn=0;
    for(nTorn=0;nTorn<nNumJugadors;nTorn++){
        pintaFitxesMoviment(nNumJugadors,astCasella,nTorn,astJugador);
    }
}

void pintaFitxesMoviment(int nNumJugadors,Caselles astCasella[MAXC],int torn,DadesJugadors astJugador[4]){
    int x,y;
    int nColor;
    int n;
    switch(torn){
        case 0:
            if(astJugador[torn].nNumCasella==0){
                nColor=2;
                x=80;
                y=40;
            }else{
                nColor=2;
                x=20;
                y=20;
            }
        break;
        case 1:
            if(astJugador[torn].nNumCasella==0){
                nColor=1;
                x=60;
                y=40;
            }else{
                nColor=1;
                x=40;
                y=20;
            }
        break;
        case 2:
            if(astJugador[torn].nNumCasella==0){
                nColor=4;
                x=40;
                y=40;
            }else{
                nColor=4;
                x=40;
                y=40;
            }
        break;
        case 3:
            if(astJugador[torn].nNumCasella==0){
                nColor=14;
                x=20;
                y=40;
            }else{
                nColor=14;
                x=20;
                y=40;
            }
        break;
    }
     
    n=astJugador[torn].nNumCasella;
    circlefill(screen,astCasella[n].nCoordenades[0]+x,astCasella[n].nCoordenades[1]+y,7,nColor);
    circle(screen,astCasella[n].nCoordenades[0]+x,astCasella[n].nCoordenades[1]+y,7,0);
            
}
 
  






     

     
     

