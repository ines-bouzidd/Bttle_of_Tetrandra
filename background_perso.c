#include "background_perso.h"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <stdio.h> 
#include <stdlib.h>  

void initBackg_perso(background_perso *b) 
{
    int i;
    
  b->image= IMG_Load("back-perso.png");     
        if (b->image== NULL) {
            fprintf(stderr, "Echec de chargement de l'image pour le bouton.\n");
            exit(1);
        }
    b->posimg.x = 0;
    b->posimg.y = 0;
    b->posimg.w = b->image->w;  
    b->posimg.h = b->image->h;
    
   
   
}

void afficherBack_perso(background_perso *b, SDL_Surface *ecran) 
{
    SDL_BlitSurface(b->image, NULL, ecran, &b->posimg);
}





void cleanBack_perso (background_perso *b)
{
    
        SDL_FreeSurface(b->image);
    SDL_Quit();
}


	 
