#include "gestionGraphique.h"


void initSDL(){
if(SDL_Init(SDL_INIT_VIDEO) < 0)  // initialisation de la SDL
    {
       printf("Erreur d'initialisation de la SDL : %s", SDL_GetError());
       SDL_Quit();
    }
}


SDL_Window * createWindow(char winName[], int winWidth, int winHeigth){
    if (SDL_Init(SDL_INIT_VIDEO) != 0){
			printf("SDL_Init Error\n");
    }
    SDL_Window *win = SDL_CreateWindow(winName, SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED, winWidth, winHeigth, SDL_WINDOW_SHOWN);
    if (win == NULL){
	printf("SDL_CreateWindow Error\n");
	SDL_Quit();
    }
    return win;
}

SDL_Renderer * createRenderer(SDL_Window *win){
	SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (ren == NULL){
		SDL_DestroyWindow(win);
		printf("SDL_CreateRenderer Error");
		SDL_Quit();
	}
	return ren;
}

SDL_Texture* loadTexture(const char* file, SDL_Renderer *ren){
	SDL_Texture *texture = NULL;
	SDL_Surface *loadedImage = SDL_LoadBMP(file);
	if (loadedImage != NULL){
		texture = SDL_CreateTextureFromSurface(ren, loadedImage);
		SDL_FreeSurface(loadedImage);
		if (texture == NULL){
			printf("Error : CreateTextureFromSurface\n");
		}
	}
	else {
		printf("Error : LoadBMP\n");
	}
	return texture;
}

void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int width, int height){
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	dst.w = width;
	dst.h = height;
	SDL_RenderCopy(ren, tex, NULL, &dst);
}
void initTTF(){
	if(TTF_Init()==-1) {
	    printf("TTF_Init: %s\n", TTF_GetError());
	    SDL_Quit();
	}
}

TTF_Font* createFont(char fontPath[], int fontSize){
	TTF_Font* font = TTF_OpenFont(fontPath, fontSize); 
	if(font==NULL){
    		printf("TTF_OpenFont: %s\n", TTF_GetError());

		SDL_Quit();
	}
	return font; 
}

void printText(int x,int y,char *text, int wsize, int hsize,TTF_Font* font, SDL_Color color, SDL_Renderer *ren){
		SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, text, color); 
		SDL_Texture* Message = SDL_CreateTextureFromSurface(ren, surfaceMessage); 
		SDL_Rect Message_rect; 
		Message_rect.x = x;  
		Message_rect.y = y; 
		Message_rect.w = wsize;
		Message_rect.h = hsize;
		SDL_RenderCopy(ren, Message, NULL, &Message_rect); 
		SDL_FreeSurface(surfaceMessage);
		SDL_DestroyTexture(Message);
}

void updateDisplay(SDL_Renderer *ren){
	SDL_RenderPresent(ren);
}

void clearRenderer(SDL_Renderer *ren){
	SDL_RenderClear(ren);
}

#include <SDL2/SDL.h>

#include <SDL2/SDL.h>
#include <stdio.h>

#include <SDL2/SDL.h>
#include <stdio.h>

#include <SDL2/SDL.h>

char processKeyboard() {
    char pdirection = ' ';
    SDL_Event e;
    int key;
    int shiftPressed = 0;
    int altGrPressed = 0;

    while (SDL_PollEvent(&e)) {
        switch (e.type) {
            case SDL_KEYDOWN:
                key = e.key.keysym.sym;
                shiftPressed = (e.key.keysym.mod & KMOD_SHIFT) ? 1 : 0;
                altGrPressed = (e.key.keysym.mod & KMOD_RALT) ? 1 : 0;

                if (shiftPressed) {
                        switch (key) {
                            case SDLK_1: pdirection = '1'; break;
                            case SDLK_2: pdirection = '2'; break;
                            case SDLK_3: pdirection = '3'; break;
                            case SDLK_4: pdirection = '4'; break;
                            case SDLK_5: pdirection = '5'; break;
                            case SDLK_6: pdirection = '6'; break;
                            case SDLK_7: pdirection = '7'; break;
                            case SDLK_8: pdirection = '8'; break;
                            case SDLK_9: pdirection = '9'; break;
                            case SDLK_0: pdirection = '0'; break;
                            case SDLK_EQUALS: pdirection = '+'; break;
                            case SDLK_RETURN: pdirection = '\r'; break;
                            case SDLK_BACKSPACE: pdirection = '\b'; break;
                            case SDLK_COMMA: pdirection = '?'; break;
                            case SDLK_SEMICOLON: pdirection = '.'; break;
                            case SDLK_COLON: pdirection = '/'; break;
                            case SDLK_ESCAPE: pdirection = '^['; break;

                            //alphabet majuscule
                            case SDLK_a: pdirection = 'A'; break;
                            case SDLK_b: pdirection = 'B'; break;
                            case SDLK_c: pdirection = 'C'; break;
                            case SDLK_d: pdirection = 'D'; break;
                            case SDLK_e: pdirection = 'E'; break;
                            case SDLK_f: pdirection = 'F'; break;
                            case SDLK_g: pdirection = 'G'; break;
                            case SDLK_h: pdirection = 'H'; break;
                            case SDLK_i: pdirection = 'I'; break;
                            case SDLK_j: pdirection = 'J'; break;
                            case SDLK_k: pdirection = 'K'; break;
                            case SDLK_l: pdirection = 'L'; break;
                            case SDLK_m: pdirection = 'M'; break;
                            case SDLK_n: pdirection = 'N'; break;
                            case SDLK_o: pdirection = 'O'; break;
                            case SDLK_p: pdirection = 'P'; break;
                            case SDLK_q: pdirection = 'Q'; break;
                            case SDLK_r: pdirection = 'R'; break;
                            case SDLK_s: pdirection = 'S'; break;
                            case SDLK_t: pdirection = 'T'; break;
                            case SDLK_u: pdirection = 'U'; break;
                            case SDLK_v: pdirection = 'V'; break;
                            case SDLK_w: pdirection = 'W'; break;
                            case SDLK_x: pdirection = 'X'; break;
                            case SDLK_y: pdirection = 'Y'; break;
                            case SDLK_z: pdirection = 'Z'; break;

                        }
                    } 
                    else {
                        switch (key) {
                            case SDLK_1: pdirection = '&'; break;
                            //case SDLK_2: pdirection = 'é'; break;
                            case SDLK_3: pdirection = '"'; break;
                            case SDLK_5: pdirection = '('; break;
                            case SDLK_6: pdirection = '-'; break;
                            //case SDLK_7: pdirection = 'è'; break;
                            case SDLK_8: pdirection = '_'; break;
                            //case SDLK_9: pdirection = 'ç'; break;
                            //case SDLK_0: pdirection = 'à'; break;
                            case SDLK_RIGHTPAREN: pdirection = ')'; break;
                            case SDLK_EQUALS: pdirection = '='; break;
                            case SDLK_ASTERISK: pdirection = '*'; break;
                            case SDLK_RETURN: pdirection = '\r'; break;
                            case SDLK_BACKSPACE: pdirection = '\b'; break;
                            case SDLK_ESCAPE: pdirection = '^['; break;


                            //alphabet minuscule
                            case SDLK_a: pdirection = 'a'; break;
                            case SDLK_b: pdirection = 'b'; break;
                            case SDLK_c: pdirection = 'c'; break;
                            case SDLK_d: pdirection = 'd'; break;
                            case SDLK_e: pdirection = 'e'; break;
                            case SDLK_f: pdirection = 'f'; break;
                            case SDLK_g: pdirection = 'g'; break;
                            case SDLK_h: pdirection = 'h'; break;
                            case SDLK_i: pdirection = 'i'; break;
                            case SDLK_j: pdirection = 'j'; break;
                            case SDLK_k: pdirection = 'k'; break;
                            case SDLK_l: pdirection = 'l'; break;
                            case SDLK_m: pdirection = 'm'; break;
                            case SDLK_n: pdirection = 'n'; break;
                            case SDLK_o: pdirection = 'o'; break;
                            case SDLK_p: pdirection = 'p'; break;
                            case SDLK_q: pdirection = 'q'; break;
                            case SDLK_r: pdirection = 'r'; break;
                            case SDLK_s: pdirection = 's'; break;
                            case SDLK_t: pdirection = 't'; break;
                            case SDLK_u: pdirection = 'u'; break;
                            case SDLK_v: pdirection = 'v'; break;
                            case SDLK_w: pdirection = 'w'; break;
                            case SDLK_x: pdirection = 'x'; break;
                            case SDLK_y: pdirection = 'y'; break;
                            case SDLK_z: pdirection = 'z'; break;
                            case SDLK_COMMA: pdirection = ','; break;
                            case SDLK_SEMICOLON: pdirection = ';'; break;
                            case SDLK_COLON: pdirection = ':'; break;
                            case SDLK_EXCLAIM: pdirection = '!'; break;
                    }
                } 

                    if (altGrPressed) {
                        switch (key) {
                            case SDLK_2: pdirection = '~'; break;
                            case SDLK_3: pdirection = '#'; break;
                            case SDLK_4: pdirection = '{'; break;
                            case SDLK_5: pdirection = '['; break;
                            case SDLK_6: pdirection = '|'; break;
                            case SDLK_7: pdirection = '`'; break;
                            case SDLK_8: pdirection = '\\'; break;
                            case SDLK_9: pdirection = '^'; break;
                            case SDLK_0: pdirection = '@'; break;
                            case SDLK_RIGHTPAREN: pdirection = ']'; break;
                            case SDLK_EQUALS: pdirection = '}'; break;
                            case SDLK_RETURN: pdirection = '\r'; break;
                            case SDLK_BACKSPACE: pdirection = '\b'; break;
                            case SDLK_ESCAPE: pdirection = '^['; break;
                        }
                    }
                }
                break;
        
    }
    return pdirection;
}

void QuitSDL(SDL_Window *win, SDL_Renderer *ren){
	SDL_DestroyWindow(win);
	SDL_DestroyRenderer(ren);
	SDL_Quit(); 
}

