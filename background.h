#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>

typedef struct {
   
    SDL_Surface *image[3];
    SDL_Rect posimg[3];
    int niveau ;
} background;


typedef struct {
   
    SDL_Surface *image[12];
   SDL_Rect posimg[12];
    
} backanim;

void initBackg(background *b);
void cleanBack(background *b);
void afficherBack(background *b,SDL_Surface *ecran);
//void afficheranim(image *im, SDL_Surface *ecran,int i);
void initanim(backanim *b);
void cleananim(backanim *b);
//void afficherBackanim(backanim *b,SDL_Surface *ecran);

#endif 


