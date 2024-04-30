#ifndef BACKGROUND_PERSO_H
#define BACKGROUND_PERSO_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>

typedef struct {
   
    SDL_Surface *image;
    SDL_Rect posimg;
} background_perso;

typedef struct {
   
    SDL_Surface *image;
    SDL_Rect posimg;
} background_perso2;


typedef struct {
   
    SDL_Surface *image;
    SDL_Rect posimg;
} background_perso3;



void initBackg_perso(background_perso *b);
void cleanBack_perso(background_perso *b);
void afficherBack_perso(background_perso *b,SDL_Surface *ecran);


#endif // GAME_H


