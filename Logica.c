/*******************************************
*
* @Arxiu: Logica.c
* @Finalitat: Implementacións de funcions i procediments del modul de logica
* @Autor/s: Àlex Cordón Vila i Sergio Gonzalez Mendoza
* @Data:10/3/2013
*
********************************************/
//Sistema


//Propies
#include "grafics.h"
//Retorna el mode de joc seleccionat,el nombre de jugadors,
void infoteclat (int *nNumJugadors,DadesJugadors astJugador[4],int anValorsdau[4],Caselles astCasella[MAXC]){
    int nJugadors=0;
    //Demanem al usuari que entri el mode E o F
    modeDeJoc (astCasella,astJugador);
    //Demanem al usuari el nombre de jugadors
    nombreJugadors (&nJugadors);
    
    //Guardem cada jugador dins un tipus anomenat DadesJugadors
    nomJugadors (nJugadors,astJugador);
    dauSortida (nJugadors,astJugador,anValorsdau);
    //Retornem el nombre de jugadors a main() per referència.
    *nNumJugadors=nJugadors;
} 

//Funció per demanar el nombre de jugadors a l'usuari
void nombreJugadors (int *nJugadors){
    int nNombreJugadors;
    do{
        printf("Nombre de jugadors: ");
        scanf("%d",&nNombreJugadors);  
        printf("\n"); 
        if (nNombreJugadors<2 || nNombreJugadors>4  ){
            printf("Error, sols es permeten de 2 a 4 jugadors.\n");
        }
    }while(nNombreJugadors<2 || nNombreJugadors>4);
    *nJugadors=nNombreJugadors;
}
//Et demana els noms dels diferents jugadors en funció del nombre de jugadors
void nomJugadors (int nJugadors,DadesJugadors astJugador[4]){
    int nCount=0;
    int i=0;
    printf("Noms dels jugadors:\n\n");
    do{
        printf("\tJugador %d: ",i+1);
        fflush(stdin);
        gets(astJugador[i].cNom);
        printf("\n");
        nCount++;
        i++;
    }while(nCount<nJugadors);  
    
}
//Et demana un mode de Joc i et retorna un boleà equivalent a la lletra entrada per teclat
void modeDeJoc (Caselles astCasella[MAXC],DadesJugadors astJugador[4]){
    char sNomFitxer[30];
    fflush(stdin);
    char cMode;
    int nMode;
    int bFitxerOk=0;
    //strcmp(sFitxer,"configuracio")
    do{
        printf("Mode de joc(E o F): ");
        //El mode de joc ha de ser E o F
        scanf("%c",&cMode);
        if (cMode!='E' && cMode!='F'){
            printf("Mode incorrecte\n");
        }
    }while (cMode!= 'E' && cMode!='F');
    if (cMode=='E'){
        inicialitzaVariables(astJugador,astCasella,0,sNomFitxer);             
    }
    if (cMode=='F'){
        do{   
            printf("\nEscriu el nom del fitxer de configuracio: ");
            scanf("%s",sNomFitxer);       
            bFitxerOk=inicialitzaVariables(astJugador,astCasella,1,sNomFitxer);
        }while(bFitxerOk==1);
    }
}
//Ens retorna un array amb els diferents valors de tirada.
int dauSortida(int nJugadors,DadesJugadors astJugador[4],int anValorsdau[4]){
    int i;
    int nNum;
    //Inicialitzem la “llavor” de la funció rand amb el temps actual 
    srand(time(NULL));
    printf("Daus de sortida:\n");
    for (i = 0; i < nJugadors; i++) {
        //Obtenim un número aleatori entre 0 i 9 
        nNum = ( rand() % 6 ) + 1;
        anValorsdau[i]=nNum;
        printf("%d- %s: %d de 6\n",i+1,astJugador[i].cNom, anValorsdau[i] );
    }
    printf("Prem Enter per continuar o Esc per sortir\n");
    return 0;
}
//Simulem els 2 valors aleatoris d'una tirada de 2 daus
void dausTirada(int *nDaus,DadesJugadors astJugador[4],int torn,int nNumJugadors,Caselles astCasella[MAXC],int *nTiradesTotals, Daus valor[1000]){
    int i=0; 
    int nNum1;
    int nSumatirades=0;
    //Sumem el valor dels dos daus de la tirada del jugador
    printf("S'han tirat els dos daus,i el resultat ha sigut: ");
    while (i<2){
        nNum1 = ( rand() % 6 ) + 1;
        if(i==0){
            //Guardem tots els valors de cada dau dins l'array valor[1000] de tipus Daus
            valor[*nTiradesTotals].nDau1=nNum1;
            printf("%d ",valor[*nTiradesTotals].nDau1);
            *nTiradesTotals=*nTiradesTotals+1;
        }
        if(i==1){
            //Guardem tots els valors de cada dau dins l'array valor[1000] de tipus Daus
            valor[*nTiradesTotals].nDau2=nNum1;
            printf("%d\n",valor[*nTiradesTotals].nDau2);
            *nTiradesTotals=*nTiradesTotals+1;
        }
        nSumatirades=nSumatirades+nNum1;
        i++;
    }
    //Esborrem la fitxa anterior per no deixar rastre i simular el moviment de la fitxa
    esborraFitxaMoviment(nNumJugadors,astCasella,torn,astJugador);
    //Sumem 1 al nombre de tirades que porta un jugador sempre que no caigui a la casella pou
    if(astJugador[torn].nPou!=0){
        nSumatirades=0;
        printf("\nNo tires! (%d)\n", astJugador[torn].nPou);
    }else{
        astJugador[torn].nTirades=astJugador[torn].nTirades+1;
    }                                                    
    astJugador[torn].nNumCasella= astJugador[torn].nNumCasella+nSumatirades;
    //Controlem els casos per tirades que sobrepassin la casella 95
    if(astJugador[torn].nNumCasella>95){
        astJugador[torn].nNumCasella= 95-(astJugador[torn].nNumCasella-95);                                    
    }
    printf("\n\nEl jugador %s es moura %d caselles fins la casella %d \n\n", astJugador[torn].cNom,nSumatirades,astJugador[torn].nNumCasella);
    astJugador[torn].nValorsDeDau=nSumatirades;
    //astJugador[torn].nTirades=astJugador[torn].nTirades+1;
    printf("Prem Enter per continuar o Esc per sortir\n");
    *nDaus=nSumatirades;
}
//Funció que incrementa el valor del torn de 0 fins a tants jugadors com hi hagi a la partida; torn inicialment serà 0.
void mouTorn(int *torn,int nNumJugadors,Caselles astCasella[MAXC],DadesJugadors astJugador[4]){
    if(astCasella[astJugador[*torn].nNumCasella].nColor==15 || astCasella[astJugador[*torn].nNumCasella].nColor==0 || astCasella[astJugador[*torn].nNumCasella].nColor==6){
        *torn=(*torn)+1;
        //Reiniciem a 0 la variable torn per tornar a començar la ronda de tirades
        if (*torn==nNumJugadors){
            *torn=0;
        }
    }
}
//Funció per controlar
void finalDePartida(DadesJugadors astJugador[4],int torn,int *sortir,Daus valor[1000],int nTiradesTotals,JugadorFinal astDades[5]){
    JugadorFinal stGuanyador;
    int n=0;
    n=astJugador[torn].nNumCasella;
    if(n==95){
        printf("\n\n\n--------------El JUGADOR %s HA GUANYAT AMB %d TIRADES----------------\n\n\n",astJugador[torn].cNom,astJugador[torn].nTirades);
        //Al finalitzar la partida es guarda el jugador guanyador i en funció del numTirades s'inclou al ranquing o no.
        strcpy(stGuanyador.cNom,astJugador[torn].cNom);
        // printf("Guanyador: %s\n",stGuanyador.cNom);
        stGuanyador.nTirades=astJugador[torn].nTirades;
        escriuRanquing(stGuanyador,astDades);
        fitxerMoviment(valor,nTiradesTotals);
        //Retornem el flag a 1 per activar la sortida del bucle.
        *sortir=1;
    }
}
int inicialitzaVariables(DadesJugadors astJugador[4],Caselles astCasella[MAXC],int nMode,char sNomFitxer[30]){
    int a=0;
    int i=0;
    int bFitxerOk=0;
    //Coordenades inicials de les fitxes
    astCasella[0].nCoordenades[0]=20;
    astCasella[0].nCoordenades[1]=570;
    //Inicialitzacio de numero de casella
    astJugador[0].nNumCasella=0; 
    astJugador[1].nNumCasella=0;
    astJugador[2].nNumCasella=0;
    astJugador[3].nNumCasella=0;
    //Inicialitzacio de color de casella
    //Primer pintem totes les caselles blanques
    for (a=0;a<MAXC;a++){
        astCasella[a].nColor=15;
    }
    switch(nMode){
        case 0:
            //Inicialització estandard        
            astCasella[6].nColor=7;
            astCasella[10].nColor=7;
            astCasella[17].nColor=7;
            astCasella[23].nColor=7;
            astCasella[30].nColor=7;
            astCasella[38].nColor=7;
            astCasella[42].nColor=7;
            astCasella[50].nColor=7;
            astCasella[64].nColor=7;
            astCasella[70].nColor=7;
            astCasella[73].nColor=7;
            astCasella[77].nColor=7;
            astCasella[82].nColor=7;
            astCasella[92].nColor=7;
            astCasella[56].nColor=7;
            astCasella[59].nColor=6;
            astCasella[80].nColor=6;
            astCasella[90].nColor=0;
            astCasella[66].nColor=0;
        break;
         
        case 1: 
            //Si a la funció modeDeJoc nMode val 1 vol dir que s'ha escollit mode Fitxer
            bFitxerOk=fitxerConfiguracio(astCasella,sNomFitxer);
        break;
    }
    //Inicialitzem les tirades que porta cada jugador a 0.
    astJugador[0].nTirades=0; 
    astJugador[1].nTirades=0;
    astJugador[2].nTirades=0;
    astJugador[3].nTirades=0; 
    //Inicnialtzem els torns d'espera de les caselles de "POU".A la 59 s'ha d'esperar 2 torns, i si cau a la casella 80 s'ha d'esperar 4 torns
    astCasella[59].nTornsBucle=2;
    astCasella[80].nTornsBucle=4; 
    //Inicialitzem els comptadors dels jugadors per a caselles de POU
    astJugador[0].nPou=0;
    astJugador[1].nPou=0;
    astJugador[2].nPou=0;
    astJugador[3].nPou=0;

    return bFitxerOk;
}

void casellaFuncio(Caselles astCasella[MAXC],int torn,DadesJugadors astJugador[4],int nNumJugadors){
    //Controlem el tipus de casella en funcio del color 7=gris
    if(astCasella[astJugador[torn].nNumCasella].nColor==7){
        printf("\nDe funcio en funcio i tiro per bon programador!\n");
        printf("Prem una tecla per continuar: ");
        getchar();
        esborraFitxaMoviment(nNumJugadors,astCasella,torn,astJugador);
        //Sumem una unitat a la casella actual per poder començar la detecció de la seguent casella gris
        astJugador[torn].nNumCasella=astJugador[torn].nNumCasella+1;
        //Sempre començem el bucle des d'una casella blanca i finalitza al trobar-ne una de gris
        while(astCasella[astJugador[torn].nNumCasella].nColor!=7 && astJugador[torn].nNumCasella!=95 ){
            astJugador[torn].nNumCasella=astJugador[torn].nNumCasella+1;
        }
        pintaFitxesMoviment(nNumJugadors,astCasella,torn,astJugador);
    }
}
void casellaBucle(Caselles astCasella[MAXC],int torn,DadesJugadors astJugador[4],int nNumJugadors){
    if(astCasella[astJugador[torn].nNumCasella].nColor==6){
        if(astJugador[torn].nPou==0){
            astJugador[torn].nPou = astCasella[astJugador[torn].nNumCasella].nTornsBucle;
            printf("nTORNSJUGADOR = %d\n", astJugador[torn].nPou);                         
            printf("\nEstas al pou!\n");
            printf("Prem una tecla per continuar: ");
            getchar();        
        }else{
            astJugador[torn].nPou=astJugador[torn].nPou-1;
            printf("\nPerds el torn! (et queden %d torns)\n", astJugador[torn].nPou);
        } 
    }
}
void casellaCore(Caselles astCasella[MAXC],int torn,DadesJugadors astJugador[4],int nNumJugadors){
    if(astCasella[astJugador[torn].nNumCasella].nColor==0){
        printf("\nEstic mort...\n");
        printf("Prem una tecla per continuar: ");
        getchar();
        esborraFitxaMoviment(nNumJugadors,astCasella,torn,astJugador);
        astJugador[torn].nNumCasella=0;
        pintaFitxesMoviment(nNumJugadors,astCasella,torn,astJugador);
    }     
}
int fitxerConfiguracio(Caselles astCasellaFitxer[MAXC],char sNomFitxer[30]){
    int a=0;
    char kk;
    char cFuncio;
    char cBucle;
    char cCore;
    char cLletra;
    int nFuncio;
    int nBucle;
    int nTornsBucle;
    int nCore;
    int bFitxerOk=0;
    FILE *f;
    f=fopen(sNomFitxer,"r");
        //Control d'error de fitxer
        if (f==NULL){
            printf("Fitxer de configuracio incorrecte!\n"); 
            bFitxerOk=1;
        }else{
            //Prelectura del fitxer
            fflush(stdin);
            fscanf(f,"%c",&cLletra);
            while(!feof(f)){              
                fflush(stdin);
                if (cLletra=='F'){
                    //Llegim el valor de la casella 
                    fscanf(f,"%d",&nFuncio);
                    //Assignem el color gris a la casella indicada pel fitxer 
                    astCasellaFitxer[nFuncio].nColor=7;
                    //LLegim el '\0' final
                    fscanf(f,"%c",&kk);
                }
                if (cLletra=='B'){
                    //Llegim el valor de la casella 
                    fscanf(f,"%d",&nBucle);
                    //Assignem el color taronja a la casella indicada pel fitxer
                    astCasellaFitxer[nBucle].nColor=6;
                    //Llegim els torns d'espera de la casella de bucle
                    fscanf(f,"%d",&nTornsBucle);
                    astCasellaFitxer[nBucle].nTornsBucle=nTornsBucle;
                    //LLegim el '\0' final
                     fscanf(f,"%c",&kk);
                           
                }
                if (cLletra=='C'){
                    //Llegim el valor de la casella 
                    fscanf(f,"%d",&nCore);
                    //Assignem el color negre a la casella indicada pel fitxer
                     astCasellaFitxer[nCore].nColor=0;
                    //LLegim el '\0' final
                    fscanf(f,"%c",&kk);
                }
                //Tornem a llegir la lletra del tipus de casella per haver fet la prelectura
                fscanf(f,"%c",&cLletra);
      
            }
    }
    fclose(f);
    return bFitxerOk;
 
}
//funcio que retorna en enter el nombre de jugadors llegits al fitxer
int llegirRanquing(JugadorFinal astDades[5]){
    //És un array amb les dades dels jugadors del fitxer
    //Variable per recorrer la cadena del fitxer
    int i=0;
    //Controla a quin jugador li assignem la informació de la cadena del fitxer
    int j=0;
    FILE *g;
    g=fopen("ranquing.bin","rb");
    //Control d'error de fitxer de ranquing
    if (g==NULL){
        printf("Error de fitxer de ranquing,el fitxer no existeix!\n"); 
    }else{
            fread(&astDades[j],sizeof(JugadorFinal),1,g);
          
            while(!feof(g) && j<5){
                j++;                
                fread(&astDades[j],sizeof(JugadorFinal),1,g);
              
                
            }   
        
        fclose(g);
    }
    return j;
}
//Funció que permet crear un ranquing i afegir-hi o no l'ultim guanyador del joc
void escriuRanquing(JugadorFinal stGuanyador,JugadorFinal astDades[5]){
    int i=0;
    int j=0;
    int k;
    FILE *g; 
    j=llegirRanquing(astDades);
    //Ordenem els jugadors un cop hi afegim el jugador que ha guanyat la partida actual
    k=ordenaJugadors(astDades,stGuanyador,j);
    //Construim el nou ranquing sobreescrivint el ja existent
    i=0;
    g=fopen("ranquing.bin","wb");
    if (g==NULL && j!=0){
        printf("Fitxer de ranquing incorrecte!\n"); 
    }else{
       
        while(i<k){
            printf("Nom: %s\n",astDades[i].cNom);
            printf("Tirades: %d\n",astDades[i].nTirades);
            fwrite(&astDades[i],sizeof(JugadorFinal),1,g);
            //fwrite(astDades[i].nTirades,sizeof(JugadorFinal),1,g);
            i++;
        }
    }
    fclose(g);
}
//Implementació de la funció que ordena els jugadors del fitxer de ranquing
int ordenaJugadors(JugadorFinal astDades[5],JugadorFinal stGuanyador,int j){
    int i=0;
    int n=0;
    int nAux;
    int nTrobat=0;
    int bOk=0;
    char cAux[30];
    //Posem un # darrere el nom del guanyador
    strcat(stGuanyador.cNom,"#");
    switch(j){
        //Si j=0 vol dir que al fitxer no hi ha cap jugador, per tant només s'ha de copiar
        case 0:
            strcpy(astDades[0].cNom,stGuanyador.cNom);        
            astDades[0].nTirades=stGuanyador.nTirades;
            j++;
        break;
       //Si hi ha 5 jugadors segur que estan ordenats per culpa del "default", dins al case 5 comparem els ranquings amb stGuanyador.nTirades
       case 5:
           n=4;
           while(i<5 && bOk==0){
               if(astDades[i].nTirades>stGuanyador.nTirades){
                   strcpy(cAux,astDades[i].cNom);
                   nAux=astDades[i].nTirades;
                   strcpy(astDades[i].cNom,stGuanyador.cNom);
                   astDades[i].nTirades=stGuanyador.nTirades;
                   bOk=1;
                   nTrobat=i;
               }
                i++;
            }
            if(bOk==1){
                    while(n>nTrobat){
                        strcpy(astDades[n].cNom,astDades[n-1].cNom);
                        astDades[n].nTirades=astDades[n-1].nTirades; 
                        n--;
                    }
                    strcpy(astDades[nTrobat+1].cNom,cAux);
                    astDades[nTrobat+1].nTirades=nAux;
            }
        break;
        //Si hi ha menys de 5 jugadors i més de 1, afegim el jugador nou a j+1 i ordenem
        default:
            strcpy(astDades[j].cNom,stGuanyador.cNom);
            astDades[j].nTirades=stGuanyador.nTirades;

            //Apliquem el mètode d'intercanvi 
            for(i=0;i<j;i++){
              
                for(n=i+1;n<j;n++){
                    
                    if(astDades[n-1].nTirades>astDades[n].nTirades){
                        nAux=astDades[n-1].nTirades;
                        strcpy(cAux,astDades[n-1].cNom);
                        
                        astDades[n-1].nTirades=astDades[n].nTirades;
                        strcpy(astDades[n-1].cNom,astDades[n].cNom);
                        
                        astDades[n].nTirades=nAux;
                        strcpy(astDades[n].cNom,cAux);
                        
                    }
                }
            }
        break;
    }
    return j;
}
//funcio que obre un fitxer anomenat moviment per escriptura i hi col·loca l'array dels valors dels daus
void fitxerMoviment(Daus valor[1000],int nTiradesTotals){
    int i=0; 
    int j=1; 
    //Per a "i" amb nombres parells seleccionem el dau 1 i per j amb valors senars el dau 2
    FILE *h;   
    h=fopen("moviment.txt","w");
        //Control d'error de fitxer
        if (h==NULL){
            printf("Fitxer de moviment incorrecte!\n"); 
        }else{
        //Copiem els valors de l'array valor[1000] al fitxer obert per escriptura
            while(i<=nTiradesTotals && j <= nTiradesTotals){
                fprintf(h,"%d",valor[i].nDau1);
                fprintf(h," "); 
                fprintf(h,"%d",valor[j].nDau2); 
                fprintf(h,"\n");                                          
                i=i+2;
                j=j+2;
            }
        }
    fclose(h);
}
void tecla(DadesJugadors astJugador[4],int *nDaus,int nNumJugadors,int *torn,Caselles astCasella[MAXC],JugadorFinal astDades[5]){
    //Hi guardem totes els tirades del joc
    Daus valor[1000];
    int bSortir = 0;
    //La variable torn1 l'utilitzem per les funcions de teclat la variable torn per les funcions de grafics
    int nTiradesTotals=0;
    int torn1=*torn;
    pintaFitxesInicials(nNumJugadors,astCasella,astJugador);
        do{
            //si detectem tecla...
            if (keypressed()) {
                //si la tecla és Enter... 
                if (key[KEY_ENTER]){
                              
                    
                    dausTirada(nDaus,astJugador,torn1,nNumJugadors,astCasella,&nTiradesTotals,valor);
                    pintaFitxesMoviment(nNumJugadors,astCasella,torn1,astJugador);
                    //Control de la casella
                    casellaBucle(astCasella,torn1,astJugador,nNumJugadors);
                    casellaFuncio(astCasella,torn1,astJugador,nNumJugadors);
                    casellaCore(astCasella,torn1,astJugador,nNumJugadors);
                    finalDePartida(astJugador,torn1,&bSortir,valor,nTiradesTotals,astDades);
                    mouTorn(&torn1,nNumJugadors,astCasella,astJugador);
                    pintaTirada(astJugador,torn1);
                    entornContornCaselles();
                    entornOrdre(astJugador,nNumJugadors,torn1);
                }
                //si premen la tecla ESC..
                if (key[KEY_ESC]){
                    allegro_exit ();              
                    printf("Adeu\n");
                    bSortir = 1;
                }
                //equival a fflushnou() en allegro. 
                clear_keybuf();
            }
        }while (!bSortir);
}


