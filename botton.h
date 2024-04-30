#ifndef BOUTON_H
#define BOUTON_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>

typedef struct {
    SDL_Surface *image[2];
    SDL_Rect posimg;
    int actif;
    Mix_Chunk *son;  // Correction de Mix_chunk à Mix_Chunk
} boutton;


void initboutonn(boutton *b[],int n,char *nomb[],int posbx[],int posby[]);
void afficherboutonn(boutton *b[],SDL_Surface *ecran,int n);
void cleanboutton(boutton *b[],int n);

#endif // BOUTON_H

