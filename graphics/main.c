#include "gestionGraphique.h"
#define sizex 20 //nb de graduations de chaque coté de 0
#define sizey 8
#define pas 30 // ecart de pixel entre chaque graduation

// use "gcc -o main *.c -Iinclude -Llib -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf"  to compile





void traceRectangleArrondi(SDL_Renderer* renderer, int x, int y, int w, int h, int r, int lineWidth, int red,int green, int blue) {
    
    SDL_SetRenderDrawColor(renderer,red, green, blue,255);

    // 1. Côtés droits (entre les coins)
    for (int i = -lineWidth / 2; i <= lineWidth / 2; i++) {
        // Côté haut
        SDL_RenderDrawLine(renderer, x + r, y + i, x + w - r, y + i);         // haut
        // Côté bas
        SDL_RenderDrawLine(renderer, x + r, y + h + i, x + w - r, y + h + i); // bas
        // Côté gauche
        SDL_RenderDrawLine(renderer, x + i, y + r, x + i, y + h - r); // gauche
        // Côté droit
        SDL_RenderDrawLine(renderer, x + w + i, y + r, x + w + i, y + h - r); // droite
    }

    // 2. Tracer les coins arrondis avec des arcs
    for (int i = 0; i <= 90; i++) {
        double angle = i * M_PI / 180.0;
        int dx = r * cos(angle);
        int dy = r * sin(angle);

        // Coin haut-gauche
        for (int i = -lineWidth / 2; i <= lineWidth / 2; i++) {
            SDL_RenderDrawPoint(renderer, x + r - dx, y + r - dy + i);
            SDL_RenderDrawPoint(renderer, x + r - dx + i, y + r - dy);
        }
        // Coin haut-droit
        for (int i = -lineWidth / 2; i <= lineWidth / 2; i++) {
            SDL_RenderDrawPoint(renderer, x + w - r + dx, y + r - dy + i);
            SDL_RenderDrawPoint(renderer, x + w - r + dx + i, y + r - dy);
        }
        // Coin bas-gauche
        for (int i = -lineWidth / 2; i <= lineWidth / 2; i++) {
            SDL_RenderDrawPoint(renderer, x + r - dx, y + h - r + dy + i);
            SDL_RenderDrawPoint(renderer, x + r - dx + i, y + h - r + dy);
        }
        // Coin bas-droit
        for (int i = -lineWidth / 2; i <= lineWidth / 2; i++) {
            SDL_RenderDrawPoint(renderer, x + w - r + dx, y + h - r + dy + i);
            SDL_RenderDrawPoint(renderer, x + w - r + dx + i, y + h - r + dy);
        }
    }
}

void initgraph(SDL_Texture *background,SDL_Renderer *ren,TTF_Font *font2, struct SDL_Color black,int graphmid_x, int graphmid_y){

    
    //affichage map
        renderTexture(background,ren,0,0,1280,720);
        SDL_SetRenderDrawColor(ren,0,0,0,255);
        for (int i=0;i<sizex;i++){
            SDL_RenderDrawLine(ren, graphmid_x+pas*i,graphmid_y-4,graphmid_x+pas*i,graphmid_y+4);
            SDL_RenderDrawLine(ren, graphmid_x-pas*i,graphmid_y-4,graphmid_x-pas*i,graphmid_y+4);
            }
            
        for (int i=0;i<sizey;i++){
            SDL_RenderDrawLine(ren, graphmid_x-4,graphmid_y+pas*i,graphmid_x+4,graphmid_y+pas*i);
            SDL_RenderDrawLine(ren, graphmid_x-4,graphmid_y-pas*i,graphmid_x+4,graphmid_y-pas*i);
        }
        updateDisplay(ren);
        
        traceRectangleArrondi(ren, 45,51,1189,49,20,1,0,0,0);   //tracé rectange noir f(x)
        traceRectangleArrondi(ren, 188,116,178,50,20,1,0,0,0);  //tracé rectange noir [a;b]
        traceRectangleArrondi(ren, 631,114,129,49,20,1,0,0,0);  //tracé rectange noir valeurs de x
        traceRectangleArrondi(ren, 1079,114,71,49,20,1,0,0,0);  //tracé rectange noir ox
        traceRectangleArrondi(ren, 1162,114,71,49,20,1,0,0,0);  //tracé rectange noir oy
            
}

int getWidth(float value) {
    
    int width = 17; // Valeur par défaut pour la largeur
    int decalage=0;
    // Ajuster la largeur en fonction de la longueur de la chaîne (nombre de chiffres avant la virgule)
    if (value <= 9.0) {
        width = 17; 
    }
    if (value>=10.0) {
        width = 25;
    }
    if (value >=100.0) {
        width = 33;
    }
    if (value >=1000.0) {
        width = 41; 
    }
    if(value >=10000.0){
        width = 49 ;
    }

    return width;
}

int getdecalage(float value) {
    
    int width = 17; // Valeur par défaut pour la largeur
    int decalage=0;
    // Ajuster la largeur en fonction de la longueur de la chaîne (nombre de chiffres avant la virgule)
    if (value <= 9) { 
        decalage=0;
    }
    if (value>=10) {
        decalage=7; 
    }
    if (value >=100) {
        decalage=14; 
    }
    if (value >=1000) {
        decalage=21; 
    }
    if(value >=10000.0){
        decalage=28;
    }

    return decalage;
}

int findxmax(int taille, float tableau[taille][2]) {
    int maxAbs = abs(tableau[0][0]);  // Initialiser maxAbs avec la valeur absolue du premier élément du tableau

    // Parcourir le tableau et mettre à jour maxAbs si une valeur absolue plus grande est trouvée
    for (int i = 1; i < taille; i++) {
        int absVal = abs(tableau[i][0]); 
        if (absVal > maxAbs) {
            maxAbs = absVal;  
        }
    }

    return maxAbs;  // Retourner la valeur absolue maximale trouvée
}
int findymax(int taille, float tableau[taille][2]) {
    int maxAbs = abs(tableau[0][0]);  // Initialiser maxAbs avec la valeur absolue du premier élément du tableau

    // Parcourir le tableau et mettre à jour maxAbs si une valeur absolue plus grande est trouvée
    for (int i = 1; i < taille; i++) {
        int absVal = abs(tableau[i][1]); 
        if (absVal > maxAbs) {
            maxAbs = absVal;  
        }
    }

    return maxAbs;  // Retourner la valeur absolue maximale trouvée
}

int main(int argc, char *argv[]){

    float value[20][2]; //ne sert à rien mais si on l'enlève l'affichage bug donc bon on le laisse...
    char car=' ';
    char *fin;
    char stringscale_x[50]={0};
    char stringscale_y[50]={0};
    char stringscale_x2[50]={0};
    char stringscale_y2[50]={0};
    char string_nbx[60]={0};
    char entry_f[60]={0};
    char entry_D[60]={0};
    int compteur=0;
    float a;
    float b;
    int nbx;
    double scale_x;
    double scale_y;
        
        
        
    int graphmid_x=639; //coord centre du repère
    int graphmid_y=452;
        
    
    int programrunning = 1;
    initSDL();
    initTTF(); 
    SDL_Window *win = createWindow("Grapheur", 1280,720);
    SDL_SetWindowFullscreen(win, 0);
    SDL_Renderer *ren = createRenderer(win);
    SDL_Texture *background = loadTexture("back.bmp",ren);
    TTF_Font *font1 = createFont("DejaVuSans-Bold.ttf", 12);
    TTF_Font *font2 = createFont("DejaVuSans.ttf", 150);
    SDL_Color white = {255,255,255};
    SDL_Color black = {0,0,0};
    SDL_Event evt;
        
        
            
    //affichage map
    initgraph(background,ren,font2, black,graphmid_x,graphmid_y);

    // Définir la couleur de dessin pour le rectangle
    SDL_SetRenderDrawColor(ren, 250, 250, 250, 255);  // Couleur gris clair (#fafafa)
    SDL_Rect rect1 = { 116, 56, 1214-116, 32 }; // {x, y, largeur, hauteur}
    SDL_Rect rect2 = { 196, 133, 361-196, 25 }; // {x, y, largeur, hauteur}
    SDL_Rect rect3 = { 637, 131, 756-637, 25 }; // {x, y, largeur, hauteur}
    SDL_Rect rect4 = { 1083, 131, 1147-1083, 25 }; // {x, y, largeur, hauteur}
    SDL_Rect rect5 = { 1165, 131, 1231-1165, 25 }; // {x, y, largeur, hauteur}



    //-----------------------------------------------------------gestion entrée------------------------------------------------------------------------------------------------------------
    

    while (car != '\r' && programrunning) {  
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                programrunning = 0;
        }}
            traceRectangleArrondi(ren, 45,51,1189,49,20,1,220,0,0);   //tracé rectange rouge f(x)
            traceRectangleArrondi(ren, 188,116,178,50,20,1,0,0,0);  //tracé rectange noir [a;b]
            traceRectangleArrondi(ren, 631,114,129,49,20,1,0,0,0);  //tracé rectange noir valeurs de x
            traceRectangleArrondi(ren, 1079,114,71,49,20,1,0,0,0);  //tracé rectange noir ox
            traceRectangleArrondi(ren, 1162,114,71,49,20,1,0,0,0);  //tracé rectange noir oy
            updateDisplay(ren);   //entrée du texte
            car=' ';
            car=processKeyboard();
            if(car!=' '&&car!='\r'){
                if(car=='\b'){
                    SDL_SetRenderDrawColor(ren, 250, 250, 250, 255);  // Couleur gris clair 
                    SDL_RenderFillRect(ren, &rect1);
                    for (int i=0 ; i<compteur ; i++){
                        
                        entry_f[i]='\0';
                        
                    }
                    compteur=0;
                    
                }
                else if(compteur<50){
                    entry_f[compteur]=car;
                    compteur+=1;
                    printText(105+compteur*15,67,&car,11,17,font2,black,ren);
                }
            }
            }
    car=' ';
    compteur=0;
    while (car != '\r' && programrunning) {  
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                programrunning = 0;
        }}  

        traceRectangleArrondi(ren, 45,51,1189,49,20,1,0,0,0);   //tracé rectange noir f(x)
        traceRectangleArrondi(ren, 188,116,178,50,20,1,220,0,0); //tracé rectange rouge [a;b]
        traceRectangleArrondi(ren, 631,114,129,49,20,1,0,0,0);  //tracé rectange noir valeurs de x
        traceRectangleArrondi(ren, 1079,114,71,49,20,1,0,0,0);  //tracé rectange noir ox
        traceRectangleArrondi(ren, 1162,114,71,49,20,1,0,0,0);  //tracé rectange noir oy
        updateDisplay(ren);   //entrée de D
        car=' ';
        car=processKeyboard();
        if(car!=' '&&car!='\r'){
            if(car!=' '&&car!='\r'){
                if(car=='\b'){

                    SDL_SetRenderDrawColor(ren, 250, 250, 250, 255);  // Couleur gris clair 
                    SDL_RenderFillRect(ren, &rect2);
                        for (int i=0 ; i<compteur ; i++){
                            
                            entry_D[i]='\0';
                            
                        }
                        compteur=0;
                }
                
            
                else if(compteur<10){
                    entry_D[compteur]=car;
                    compteur+=1;
                    printText(195+compteur*15,133,&car,9,15,font2,black,ren);
                }
            }
            }
        }
    car=' ';
    compteur=0;
    while (car != '\r' && programrunning) {  
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                programrunning = 0;
        }}
                    traceRectangleArrondi(ren, 45,51,1189,49,20,1,0,0,0);   //tracé rectange noir f(x)
                    traceRectangleArrondi(ren, 188,116,178,50,20,1,0,0,0);  //tracé rectange noir [a;b]
                    traceRectangleArrondi(ren, 631,114,129,49,20,1,220,0,0);  //tracé rectange rouge valeurs de x
                    traceRectangleArrondi(ren, 1079,114,71,49,20,1,0,0,0);  //tracé rectange noir ox
                    traceRectangleArrondi(ren, 1162,114,71,49,20,1,0,0,0);  //tracé rectange noir oy
                    updateDisplay(ren);   //entrée des subdivisions
                    car=' ';
                    car=processKeyboard();
                    if(car!=' '&&car!='\r'){
                        
                            if(car=='\b'){
                                
                            
                                
                                SDL_SetRenderDrawColor(ren, 250, 250, 250, 255);  // Couleur gris clair 
                                SDL_RenderFillRect(ren, &rect3);
                                    for (int i=0 ; i<compteur ; i++){
                                        
                                        string_nbx[i]='\0';
                                        
                                    }
                                    compteur=0;
                            
                            }
                        
                        else if(compteur<7){
                            string_nbx[compteur]=car;
                            compteur+=1;
                            printText(630+compteur*15,132,&car,9,15,font2,black,ren);
                        }
                    }
                    
                }
                    
                    printf(" LA String NBX %s \n",string_nbx);
   
    car=' ';
    compteur=0;
    while (car != '\r' && programrunning) {  
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                programrunning = 0;
        }}
        traceRectangleArrondi(ren, 45,51,1189,49,20,1,0,0,0);   //tracé rectange noir f(x)
        traceRectangleArrondi(ren, 188,116,178,50,20,1,0,0,0);  //tracé rectange noir [a;b]
        traceRectangleArrondi(ren, 631,114,129,49,20,1,0,0,0);  //tracé rectange noir valeurs de x
        traceRectangleArrondi(ren, 1079,114,71,49,20,1,220,0,0);  //tracé rectange rouge ox
        traceRectangleArrondi(ren, 1162,114,71,49,20,1,0,0,0);  //tracé rectange noir oy
        updateDisplay(ren);   //graduation x
        car=' ';
        car=processKeyboard();
        if(car!=' '&&car!='\r'){
            if(car=='\b'){
                                
                            
                                
                SDL_SetRenderDrawColor(ren, 250, 250, 250, 255);  // Couleur gris clair 
                SDL_RenderFillRect(ren, &rect4);
                    for (int i=0 ; i<compteur ; i++){
                        
                        stringscale_x[i]='\0';
                        
                    }
                    compteur=0;
            
            }
            else if(compteur<4){
                stringscale_x[compteur]=car;
                compteur+=1;
                printText(1075+compteur*15,133,&car,9,15,font2,black,ren);
            }
        }
        }
    car=' ';
    compteur=0;
    while (car != '\r' && programrunning) {  
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                programrunning = 0;
        }}
        traceRectangleArrondi(ren, 45,51,1189,49,20,1,0,0,0);   //tracé rectange noir f(x)
        traceRectangleArrondi(ren, 188,116,178,50,20,1,0,0,0);  //tracé rectange noir [a;b]
        traceRectangleArrondi(ren, 631,114,129,49,20,1,0,0,0);  //tracé rectange noir valeurs de x
        traceRectangleArrondi(ren, 1079,114,71,49,20,1,0,0,0);  //tracé rectange noir ox
        traceRectangleArrondi(ren, 1162,114,71,49,20,1,220,0,0);  //tracé rectange rouge oy
        updateDisplay(ren);   //graduation y
        car=' ';
        car=processKeyboard();
        if(car!=' '&&car!='\r'){
            if(car=='\b'){
                                
                            
                                
                SDL_SetRenderDrawColor(ren, 250, 250, 250, 255);  // Couleur gris clair 
                SDL_RenderFillRect(ren, &rect5);
                    for (int i=0 ; i<compteur ; i++){
                        
                        string_nbx[i]='\0';
                        
                    }
                    compteur=0;
            
            }
            else if(compteur<4){
                stringscale_y[compteur]=car;
                compteur+=1;
                printText(1160+compteur*15,133,&car,9,15,font2,black,ren);
            }
        }
        }
    car=' ';
    traceRectangleArrondi(ren, 1162,114,71,49,20,1,0,0,0);
    updateDisplay(ren);
       
//extractio des bornes de l'ensemble de définition
if (sscanf(entry_D, "[%f;%f]", &a, &b) == 2) {
    printf("a = %.2f\n", a);
    printf("b = %.2f\n", b);
} else {
    printf("Erreur de parsing.\n");
}    


    
    
    if(string_nbx[0]=='\0'){
        printText(673+compteur*15,132,"auto",40,15,font2,black,ren);
        nbx=(b-a)*10;     //valeur par défaut de subdivisions
    }
    else{
        nbx=atoi(string_nbx);
    }
    


//retourne entry_f la chaine de caractères de la fonction, entry_D, l'intervalle, a et b les bornes de l'intervalle, nbx le nombre de subdivisons, scale_x et scale_y la valeurs des graduations

//  ----------------------------------------------------------------------reste du programme----------------------------------------------------------------------------------



//exemple avec la fonction sin à remplacer

float values[nbx][2];  // Tableau pour stocker les couples (x, sin(x))

    float steppp = (b - a) / (nbx - 1);  // Calcul de l'écart entre chaque x

    // Remplir le tableau avec les valeurs de x et sin(x)
    for (int i = 0; i < nbx; i++) {
        values[i][0] = a + i * steppp;           // Calcul de x
        values[i][1] = sin(values[i][0]);       // Calcul de f(x) = sin(x)
    }







 //-------------------------------------------------------------------------------tracé----------------------------------------------------------------------------------------
            
            //définition des valeurs par défaut de scale
            if(stringscale_x[0]=='\0'){
        
                scale_x=findxmax(nbx,values)/18;     //valeur par défaut d'échelle x
            }
            else{
                scale_x = atof(stringscale_x); //conversion des entrées txt en float et int et valeurs par défaut
            }
            
            if(stringscale_y[0]=='\0'){
                
                scale_y=findymax(nbx,values)/18;     //valeur par défaut d'échelle x
            }
            else{
                scale_y = atof(stringscale_y); //conversion des entrées txt en float et int et valeurs par défaut
            }
                
            printf("entree utilisateur : %s\n [a;b]: %s\n subdivisions : %i\n scale_x: %f\n scale_y: %f", entry_f,entry_D,nbx,scale_x,scale_y);
            printf("DEBUG SCALEX %s DEBUG SCALEX %s ",stringscale_x,stringscale_y);

            //conversion et affichage échelle
            


            SDL_SetRenderDrawColor(ren,255,0,0,255);
            float scale2_x=pas/scale_x;
            float scale2_y=pas/scale_y;
            sprintf(stringscale_x2,"%.1f",2*scale_x);
            sprintf(stringscale_y2,"%.1f",2*scale_y);
            int w_x=getWidth(2*scale_x);
            int w_y=getWidth(2*scale_y);
            int decal_x=getdecalage(2*scale_x)/2;
            int decal_y=getdecalage(2*scale_y);
            printText(graphmid_x+52-decal_x,graphmid_y+10,stringscale_x2,w_x,17,font2,black,ren);
            printText(graphmid_x-35-decal_y,graphmid_y-67,stringscale_y2,w_y,17,font2,black,ren);
            //SDL_RenderDrawLine(ren, 550,343,550+2*scale2,343-4*scale2);
            for (int i=1;i<nbx;i++){ // tracé de la fonction
                if((graphmid_y-values[i][1]*scale2_y>215)&&(graphmid_y-values[i][1]*scale2_y<680)&&(graphmid_y-values[i-1][1]*scale2_y>215)&&(graphmid_y-values[i-1][1]*scale2_y<680)&&(graphmid_x+values[i][0]*scale2_x<1217)&&(graphmid_x+values[i][0]*scale2_x>38)&&(graphmid_y-values[i-1][1]*scale2_y<680)&&(graphmid_x+values[i-1][0]*scale2_x<1217)&&(graphmid_x+values[i-1][0]*scale2_x>38)){
                    SDL_RenderDrawLine(ren, graphmid_x+values[i-1][0]*scale2_x,graphmid_y-values[i-1][1]*scale2_y,graphmid_x+values[i][0]*scale2_x,graphmid_y-values[i][1]*scale2_y);
                }
                
            }

            updateDisplay(ren);

            
            
            
            while(programrunning==1){  
                SDL_WaitEvent(&evt);
                if(evt.type == SDL_QUIT){  //fermer la fenêtre
                programrunning = 0;}
        
 
            }
}

