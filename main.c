/*******************************************
*
* @Arxiu: main.c
* @Finalitat: Procediment principal des d'on s'executen les funcions generals
* @Autor/s: Àlex Cordón Vila i Sergio Gonzalez Mendoza
* @Data:10/3/2013
*
********************************************/

//Propies
#include "grafics.h"
#include"logica.h"
int main() {
    //Tipus propi per guardar la info de tots els jugadors
    DadesJugadors astJugador[4];
    //Tipus propi per guardar la info de totes les caselles del mode E
    Caselles astCasella[MAXC];
    //Tipus propi per guardar la info del fitxer de rànquing
    JugadorFinal astDades[5];
    //Caselles astCasellaFitxer[MAXC];
    //Array on hi guardem tots els valors dels dos daus que han sortit al llarg de la partida
    Daus astMoviment[2000];
    //Boolea per escollir el mode de Joc. 0=Est 1=Fitxer
    //Hi guardem el nombre de jugadors a la partida
    int nNumJugadors;
    int nDaus=0;
    //Hi guardem el nombre de jugadors que hi ha al fitxer
    int nJugadorsFitxer=0;
    //Valors dels daus inicials
    int anValorsdau[4];
    
    int nError;
    //Inicialitzem sempre el valor del torn a 0 per controlar les tirades de cada jugador
    int torn=0;
    //Color de la finestra de comandes
    system("color 1F");
    //Inicialització d'allegro
    allegro_init ();
    //Obrim el fitxer de rànquings per guardar-ne la iformacio i mostrar-la al usuari sobre l'entorn
    nJugadorsFitxer=llegirRanquing(astDades);
    //Demanem al jugador les dades per iniciar el joc: Mode,NumJugadors i daus inicials          
    infoteclat(&nNumJugadors,astJugador,anValorsdau,astCasella);
    //Activar teclat
    install_keyboard ();
    //Inici de la finestra gràfica
    nError=set_gfx_mode(GFX_SAFE, 800, 600, 0, 0);
    
    if (nError==0){ 
        entorn(nNumJugadors,astJugador,nDaus,anValorsdau,torn,astCasella,nJugadorsFitxer,astDades);
        tecla(astJugador,&nDaus,nNumJugadors,&torn,astCasella,astDades);  
    }else{
        allegro_message("No es pot crear la finestra\n%s\n",allegro_error); 
        printf("No es pot crear la finestra\n%s\n",allegro_error);
    }
    system("pause");
    allegro_exit ();
}
END_OF_MAIN();
