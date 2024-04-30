#include "background.h"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <stdio.h> 
#include <stdlib.h>  

void initBackg(background *b) 
{
    int i;
    char *nom[] = {"backg0.png", "backg1.png", "backg2.png"};

    for (i = 0; i < 3; i++) {
        b->image[i] = IMG_Load(nom[i]);
        if (b->image[i] == NULL) {
            fprintf(stderr, "Echec de chargement de l'image : %s.\n", IMG_GetError());
            exit(1);
        }
    }
    for (i=0;i<3;i++)
    {
    b->posimg[i].x = 0;
    b->posimg[i].y = 0;
    b->posimg[i].w = b->image[i]->w;  
    b->posimg[i].h = b->image[i]->h;
    }
   
    b->niveau=0;
}

void afficherBack(background *b, SDL_Surface *ecran) 
{
    SDL_BlitSurface(b->image[b->niveau], NULL, ecran, &b->posimg[b->niveau]);
}





void cleanBack (background *b)
{
    int i;


    for (i = 0; i < 3; i++) 
    {
        SDL_FreeSurface(b->image[i]);
    }

    SDL_Quit();
}


	 
void initanim(backanim *b) 
{
    int i;
    char *nom[] = {"1.png", "2.png","3.png","4.png", "5.png", "6.png","7.png","8.png", "9.png","10.png", "11.png","12.png"};// "1.png", "2.png","6.png","7.png", "8.png", "9.png","10.png","4.png", "5.png", "3.png"

    for (i = 0; i < 11; i++) {
        b->image[i] = IMG_Load(nom[i]);
        if (b->image[i] == NULL) {
            fprintf(stderr, "Echec de chargement de l'image : %s.\n", IMG_GetError());
            exit(1);
        }
    }
    for (i=0;i<11;i++)
    {
    b->posimg[i].x = 0;
    b->posimg[i].y = 0;
    b->posimg[i].w = 0;
    b->posimg[i].h = 0;
    }
    
   
   
}
	
void cleananim(backanim *b)
{
    int i;


    for (i = 0; i < 11; i++) 
    {
        SDL_FreeSurface(b->image[i]);
    }

    SDL_Quit();
}

	
/*
 void afficherBackanim(backanim *b,SDL_Surface *ecran)
 {   int i;
 	for(i=0;i<9;i++)
         SDL_BlitSurface(b->image[i], NULL, ecran, &b->posimg[i]);
}

*/

    
